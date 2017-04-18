/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef PHYRE_SAMPLES_COMMON_H
#define PHYRE_SAMPLES_COMMON_H

namespace Phyre
{
	// Description:
	// The namespace for Phyre samples common classes and functions.
	namespace PSamplesCommon
	{

		// Description:
		// Finds the first object of the templated type in the cluster.
		// Template Arguments:
		// CLASS - The class of object to find.
		// Arguments:
		// cluster - The cluster to search for objects.
		// Returns:
		// A pointer to the first object of the templated type if found otherwise NULL.
		template <class CLASS>
		CLASS *FindFirstInstanceInCluster(PCluster &cluster)
		{
			CLASS *result = NULL;
			PCluster::PObjectIteratorOfType<CLASS> it(cluster);
			if(it)
				result = &*it;

			return result;
		}

		// Description:
		// Finds the asset referenced by the specified ID and file pattern.
		// Template Arguments:
		// T - The type of asset to find.
		// Arguments:
		// id - The ID pattern to use to search for the asset.
		// file - The file pattern to use to search for the asset.
		// cluster - Receives the cluster the asset was found within.
		// Returns:
		// The pointer to an asset if one could be found; otherwise NULL is returned.
		template <typename T>
		T *FindAssetRefObjWithCluster(const PChar *id, const PChar *file, const PCluster *&cluster)
		{
			PSharray<PAssetReference *> assetReferences;
			PAssetReference::Find(assetReferences, id, file, &PHYRE_CLASS(T));

			if (assetReferences.getCount() > 0)
			{
#if defined(_DEBUG) || defined(_DEBUGOPT)
				if (assetReferences.getCount() > 1)
					PHYRE_WARN("Multiple results returned when looking for %ss%s%s%s%s\n",
					PHYRE_CLASS(T).getName(),
					id ? " called " : "", id ? id : "",
					file ? " in file " : "", file ? file : "");
#endif // defined(_DEBUG) || defined(_DEBUGOPT)
				const PAssetReference *ar = assetReferences[0];
				cluster = ar->getCluster();
				return (T *)&ar->getAsset();
			}

			return NULL;
		}

		// Description:
		// Finds the asset referenced by the specified ID and file pattern.
		// Template Arguments:
		// T - The type of asset to find.
		// Arguments:
		// id - The ID pattern to use to search for the asset.
		// file - The file pattern to use to search for the asset.
		// Returns:
		// The pointer to an asset if one could be found; otherwise NULL is returned.
		template <typename T>
		T *FindAssetRefObj(const PChar *id, const PChar *file)
		{
			const PCluster *cluster = NULL;
			return FindAssetRefObjWithCluster<T>(id, file, cluster);
		}

		// Description:
		// The PLoadedClusterArray class is a helper class for storing an array of loaded clusters and destroying them at shutdown.
		class PLoadedClusterArray : public PSharray<PCluster *>
		{
		public:
			// Description:
			// Deletes all of the clusters in the array and then frees the memory used to store the array.
			inline void clear()
			{
				PUInt32		count		= getCount();
				PCluster	**clusters	= getArray();
				while(count--)
					delete *clusters++;
				resize(0);
			}
		};

		// Description:
		// Gets a dynamic property value from a component using pointer types.
		// Template Arguments:
		// T - The type of the dynamic property.
		// Arguments:
		// component - The component to get the type from.
		// name - The name of the property.
		// Returns:
		// A pointer to the dynamic property value if it was found; otherwise NULL is returned.
		template<typename T>
		inline T* GetDynamicPropertyValuePtr(const Phyre::PComponent *component, const PChar *name)
		{
			const Phyre::PClassDescriptor *cd = &component->getComponentType();		
			const Phyre::PClassDataMember *nameMember = cd->getMemberByName<Phyre::PClassDataMember>(name);
			if (nameMember)
			{
				const Phyre::PBase *base = component; 
				const void *namePtr = nameMember->data(*base);
				return (T *)namePtr;
			}
			else
			{
				return (T *)NULL;
			}
		}

		// Description:
		// Gets a dynamic property from a component using pointer types.
		// Template Arguments:
		// T - The type of the dynamic property.
		// Arguments:
		// component - The component to get the type from.
		// name - The name of the property.
		// Returns
		// A pointer to the dynamic property if it was found; otherwise NULL is returned.
		template<typename T>
		inline T* GetDynamicPropertyPtr(const Phyre::PComponent *component, const PChar *name)
		{
			const Phyre::PClassDescriptor *cd = &component->getComponentType();
			const Phyre::PClassDataMember *nameMember = cd->getMemberByName<Phyre::PClassDataMember>(name);
			if (nameMember)
			{
				const Phyre::PBase *base = component;
				const void *namePtr = nameMember->data(*base);
				return *((T **)namePtr);
			}
			else
			{
				return (T *)NULL;
			}
		}

		// Description:
		// Checks if a dynamic property exists on a component.
		// Arguments:
		// component - The component to get the type from.
		// name - The name of the property.
		// Return Value List:
		// true : The dynamic property exists.
		// false : The dynamic property does not exist.
		inline bool DynamicPropertyIsPresent(const Phyre::PComponent *component, const PChar *name)
		{
			const Phyre::PClassDescriptor *cd = &component->getComponentType();
			const Phyre::PClassDataMember *nameMember = cd->getMemberByName<Phyre::PClassDataMember>(name);
			return (nameMember) ? true : false;
		}

	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace

#endif //! PHYRE_SAMPLES_COMMON_H
