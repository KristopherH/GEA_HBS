/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#include <fios2.h>

using namespace Phyre;

namespace Phyre
{
	namespace PSamplesCommon
	{
		namespace PInternal
		{
			// Description:
			// The FIOS2 default maximum path.
			#define PD_MAX_PATH_LENGTH_FIOS2 256

			// Buffers for FIOS2 initialization.
			// These are the typical values that a game might use, but they should be adjusted as needed.
			// They are of type int64_t to avoid alignment issues.

			// Description:
			// The storage for FIOS2 operations.
			static int64_t s_fios2OpStorage[SCE_FIOS_OP_STORAGE_SIZE(64, PD_MAX_PATH_LENGTH_FIOS2) / sizeof(int64_t) + 1]; 

			// Description:
			// The storage for FIOS2 chunks: 2048 chunks, 64KiB.
			static int64_t s_fios2ChunkStorage[SCE_FIOS_CHUNK_STORAGE_SIZE(2048) / sizeof(int64_t) + 1];

			// Description:
			// The storage for FIOS2 file handles.
			static int64_t s_fios2FileHandleStorage[SCE_FIOS_FH_STORAGE_SIZE(16, PD_MAX_PATH_LENGTH_FIOS2) / sizeof(int64_t) + 1]; 

			// Description:
			// The storage for FIOS2 directory handles.
			static int64_t s_fios2DirectoryHandleStorage[SCE_FIOS_DH_STORAGE_SIZE(4, PD_MAX_PATH_LENGTH_FIOS2) / sizeof(int64_t) + 1];

			// Description:
			// The FIOS2 dearchiver context.
			static SceFiosPsarcDearchiverContext s_fios2DearchiverContext = SCE_FIOS_PSARC_DEARCHIVER_CONTEXT_INITIALIZER;

			// Description:
			// The FIOS2 dearchiver work buffer.
			static char s_fios2DearchiverWorkBuffer[SCE_FIOS_PSARC_DEARCHIVER_WORK_BUFFER_SIZE] __attribute__((aligned(SCE_FIOS_PSARC_DEARCHIVER_WORK_BUFFER_ALIGNMENT)));

			// Description:
			// The index value used for the FIOS2 archive media layer.
			static int s_fios2ArchiveIndex = 0;

			// Description:
			// The FIOS2 mount buffer.
			static SceFiosBuffer s_mountBuffer = SCE_FIOS_BUFFER_INITIALIZER;

		} //! End of PInternal namespace

		//
		// PFIOSArchiveOrbis implementation
		//

		// Description:
		// The constructor for the PFIOSArchiveOrbis class.
		PFIOSArchiveOrbis::PFIOSArchiveOrbis()
			: m_fileHandle(0)
		{
		}

		//
		// PFIOSInterfaceOrbis implementation
		//

		// Description:
		// Initializes FIOS based on the specified parameters.
		// Arguments:
		// fiosInterfaceParams : The parameters to be used for initializing FIOS.
		// Return Value List:
		// PE_RESULT_UNKNOWN_ERROR : A FIOS error occurred.
		// PE_RESULT_NO_ERROR : FIOS initialized successfully.
		PResult PFIOSInterfaceOrbis::Initialize(const PFIOSInterfaceParams &fiosInterfaceParams)
		{
			using namespace PInternal;

			(void)&fiosInterfaceParams;
			SceFiosParams params = SCE_FIOS_PARAMS_INITIALIZER;
			params.opStorage.pPtr			= s_fios2OpStorage;
			params.opStorage.length			= sizeof(s_fios2OpStorage);
			params.chunkStorage.pPtr		= s_fios2ChunkStorage;
			params.chunkStorage.length		= sizeof(s_fios2ChunkStorage);
			params.fhStorage.pPtr			= s_fios2FileHandleStorage;
			params.fhStorage.length			= sizeof(s_fios2FileHandleStorage);
			params.dhStorage.pPtr			= s_fios2DirectoryHandleStorage;
			params.dhStorage.length			= sizeof(s_fios2DirectoryHandleStorage);
			params.pathMax					= PD_MAX_PATH_LENGTH_FIOS2;

			int err = sceFiosInitialize(&params);
			if(err != SCE_FIOS_OK) 
				return PHYRE_SET_LAST_ERROR(PE_RESULT_UNKNOWN_ERROR, "Error from sceFiosInitialize() 0x%08x", err);

			// Add a dearchiver I/O filter. Both the context struct and the work buffer must last for the lifetime of the dearchiver.
			s_fios2DearchiverContext.workBufferSize	= sizeof(s_fios2DearchiverWorkBuffer);
			s_fios2DearchiverContext.pWorkBuffer	= s_fios2DearchiverWorkBuffer;
			err = sceFiosIOFilterAdd(s_fios2ArchiveIndex, sceFiosIOFilterPsarcDearchiver, &s_fios2DearchiverContext);
			if(err != SCE_FIOS_OK) 
				return PHYRE_SET_LAST_ERROR(PE_RESULT_UNKNOWN_ERROR, "Error from sceFiosIOFilterAdd() 0x%08x", err);

			return PE_RESULT_NO_ERROR;
		}

		// Description:
		// Mounts an archive with the specified name.
		// Arguments:
		// name : The name of the archive file to mount.
		// archive : The archive object to store FIOS information.
		// Return Value List:
		// PE_RESULT_OBJECT_OF_SAME_NAME_EXISTS : The archive is already mounted.
		// PE_RESULT_UNKNOWN_ERROR : A FIOS error occurred.
		// PE_RESULT_NO_ERROR : The archive was mounted successfully.
		PResult PFIOSInterfaceOrbis::MountArchive(const PChar *name, PFIOSArchive &archive)
		{
			if(archive.m_fileHandle)
				return PHYRE_SET_LAST_ERROR(PE_RESULT_OBJECT_OF_SAME_NAME_EXISTS, "The archive has already been mounted");

			const PChar *streamPrefix = PSerialization::PStreamFile::GetStreamPrefix();
			SceFiosSize result = -1;
			const PChar *filenameUsed = name;
			if(streamPrefix)
			{
				size_t fullLength = strlen(name) + strlen(streamPrefix) + 1;
				PChar *fullname = (PChar *)alloca(fullLength);
				PHYRE_SNPRINTF(fullname, fullLength, "%s%s", streamPrefix, name);
				result = sceFiosArchiveGetMountBufferSizeSync(NULL, fullname, NULL);
				if(result >= 0)
					filenameUsed = fullname;
			}

			// Find out how much memory is needed to mount the archive.
			if(result < 0)
			{
				result = sceFiosArchiveGetMountBufferSizeSync(NULL, name, NULL);
				if (result < 0)
					return PHYRE_SET_LAST_ERROR(PE_RESULT_UNKNOWN_ERROR, "Error from sceFiosArchiveGetMountBufferSizeSync() 0x%08x", (PInt32)result);
			}

			// Allocate a mount buffer.
			PInternal::s_mountBuffer.length = (size_t)result;
			PInternal::s_mountBuffer.pPtr = PHYRE_ALLOCATE_ALIGNED(PUInt8, PInternal::s_mountBuffer.length, 8);
			if (!PInternal::s_mountBuffer.pPtr)
				return PHYRE_SET_LAST_ERROR(PE_RESULT_OUT_OF_MEMORY, "Unable to allocate %d bytes for mount buffer", (PUInt32)PInternal::s_mountBuffer.length);

			// Mount the archive.
			int err = sceFiosArchiveMountSync(NULL, &archive.m_fileHandle, filenameUsed, PSerialization::PStreamFileOrbis::GetFIOS2ArchiveMountPoint(), PInternal::s_mountBuffer, NULL);
			if(err != SCE_FIOS_OK)
				return PHYRE_SET_LAST_ERROR(PE_RESULT_UNKNOWN_ERROR, "Error from sceFiosArchiveMountSync() 0x%08x", err);

			PHYRE_ASSERT(sceFiosIsValidHandle(archive.m_fileHandle));
			return PE_RESULT_NO_ERROR;
		}

		// Description:
		// Unmounts the specified archive.
		// Arguments:
		// archive : The archive object that stores FIOS information.
		// Return Value List:
		// PE_RESULT_UNINITIALIZED_DATA : The archive is not mounted.
		// PE_RESULT_UNKNOWN_ERROR : A FIOS error occurred.
		// PE_RESULT_NO_ERROR : The archive was unmounted successfully.
		PResult PFIOSInterfaceOrbis::UnmountArchive(PFIOSArchive &archive)
		{
			SceFiosFH fileHandle = archive.m_fileHandle;
			if(!fileHandle)
				return PHYRE_SET_LAST_ERROR(PE_RESULT_UNINITIALIZED_DATA, "The archive has not been mounted");
			int err = sceFiosArchiveUnmountSync(NULL, fileHandle);
			archive.m_fileHandle = 0;
			if(err != SCE_FIOS_OK)
				return PHYRE_SET_LAST_ERROR(PE_RESULT_UNKNOWN_ERROR, "Error from sceFiosArchiveUnmountSync() 0x%08x", err);

			// Free the memory used by the mount buffer
			if (PInternal::s_mountBuffer.pPtr)
			{
				PHYRE_FREE(PInternal::s_mountBuffer.pPtr);
				PInternal::s_mountBuffer.pPtr = NULL;
			}

			return PE_RESULT_NO_ERROR;
		}

		// Description:
		// Terminates the use of FIOS.
		// Return Value List:
		// PE_RESULT_UNKNOWN_ERROR : A FIOS error occurred.
		// PE_RESULT_NO_ERROR : The FIOS interface terminated successfully.
		PResult PFIOSInterfaceOrbis::Terminate()
		{
			int err = sceFiosIOFilterRemove(PInternal::s_fios2ArchiveIndex);
			if (err != SCE_FIOS_OK)
				return PHYRE_SET_LAST_ERROR(PE_RESULT_UNKNOWN_ERROR, "Error from sceFiosIOFilterRemove() 0x%08x", err);
			sceFiosTerminate();
			return PE_RESULT_NO_ERROR;
		}

	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace
