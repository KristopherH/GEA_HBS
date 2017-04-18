/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef PHYRE_SAMPLES_COMMON_FIOS_ORBIS_H
#define PHYRE_SAMPLES_COMMON_FIOS_ORBIS_H

namespace Phyre
{
	namespace PSamplesCommon
	{
		// Description:
		// Contains information about archives mounted with FIOS on the PlayStation(R)4 platform.
		class PFIOSArchiveOrbis
		{
		public:
			PFIOSArchiveOrbis();
			SceFiosFH m_fileHandle;	// The FIOS file handle.
		};

		// Description:
		// Provides an interface for initializing and terminating FIOS on the PlayStation(R)4 platform.
		class PFIOSInterfaceOrbis
		{
		public:
			static PResult Initialize(const PFIOSInterfaceParams &fiosInterfaceParams);
			static PResult MountArchive(const PChar *name, PFIOSArchive &archive);
			static PResult UnmountArchive(PFIOSArchive &archive);
			static PResult Terminate();
		};

	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace

#endif //! PHYRE_SAMPLES_COMMON_FIOS_ORBIS_H
