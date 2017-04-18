/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef PHYRE_SAMPLES_COMMON_SCRIPTING_H
#define PHYRE_SAMPLES_COMMON_SCRIPTING_H

namespace Phyre
{
	namespace PSamplesCommon
	{
		Phyre::PResult TryReloadScriptedComponentScript(Phyre::PGameplay::PScriptedComponent *sc, const Phyre::PChar *mediaPath);
		void ValidScriptComponents(Phyre::PWorld &world);
	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace

#endif //! PHYRE_SAMPLES_COMMON_SCRIPTING_H

