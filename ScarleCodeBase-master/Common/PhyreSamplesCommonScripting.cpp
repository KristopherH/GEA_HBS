/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#include <Phyre.h>
#include <Geometry/PhyreGeometry.h>
#include <Gameplay/PhyreGameplay.h>
#include <Scripting/PhyreScripting.h>
#include <Character/PhyreCharacter.h>

namespace Phyre
{
	namespace PSamplesCommon
	{

		using namespace PScripting;

		//!
		//! Script helper functions
		//!

		// Description:
		// Attempts to reload a scripted component script.
		// Arguments:
		// sc - The scripted component.
		// mediaPath - The media path.
		// Return Value List:
		// PE_RESULT_OBJECT_NOT_FOUND - The scripted component argument was NULL.
		// PE_RESULT_NO_ERROR - The scripted component script was reloaded successfully.
		// Other - An error from a sub method.
		PResult TryReloadScriptedComponentScript(PGameplay::PScriptedComponent *sc, const PChar *mediaPath)
		{
			// Check it's present.
			if (!sc)
				return PE_RESULT_OBJECT_NOT_FOUND;

			// Get the suspended state
			bool wasSuspended = !sc->getIsRunning();

			// Suspend the script if it wasn't already.
			if (!wasSuspended)
				sc->suspendScript();

			// Close the old context and remove from scheduler
			PHYRE_TRY(sc->uninitializeScript());

			// Build a string to the path
			PStringBuilder path(mediaPath);

			// Load the requested script
			bool reloaded = ReloadScript(path.c_str(), sc->getScript()) == PE_RESULT_NO_ERROR;

			// Add back into scheduler - using the new context (overrides the default)
			PHYRE_TRY(sc->initializeScript());

			// If it was suspended put it back into the same state.
			if (wasSuspended)
				sc->suspendScript();

			// Message
			if(reloaded)
				PHYRE_PRINTF("RELOADED SCRIPT: %s\n", sc->getScript()->m_sourceName.c_str());

			return PE_RESULT_NO_ERROR;
		}

		// Description:
		// Validates the scripts on components.
		// Arguments:
		// world - The world in which to validate components' scripts.
		void ValidScriptComponents(Phyre::PWorld &world)
		{
			// Warn if scripts are unset for any of the character components
			for (PWorld::PObjectIteratorOfType<PCharacter::PCharacterControllerComponent> it(world); it; ++it)
				if (it->getScript() == NULL)
					PHYRE_WARN("Character controller component is missing a script. This component will not be updated.\n");
#ifdef PHYRE_ENABLE_PHYSICS
			for (PWorld::PObjectIteratorOfType<PCharacter::PPhysicsCharacterControllerComponent> it(world); it; ++it)
				if (it->getScript() == NULL)
					PHYRE_WARN("Physics character controller component is missing a script. This component will not be updated. A default script 'DefaultCharacterController.lua' is available in the Media\\Scripts\\ directory.\n");
#endif //! PHYRE_ENABLE_PHYSICS
			for (PWorld::PObjectIteratorOfType<PCharacter::PCharacterAnimationComponent> it(world); it; ++it)
				if (it->getScript() == NULL)
					PHYRE_WARN("Character animation component is missing a script. This component will not be updated. A default script 'DefaultCharacterAnimation.lua' is available in the Media\\Scripts\\ directory.\n");
		}

	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace
