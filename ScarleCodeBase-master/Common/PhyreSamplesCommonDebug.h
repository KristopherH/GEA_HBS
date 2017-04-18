/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef PHYRE_SAMPLES_COMMON_DEBUG_H
#define PHYRE_SAMPLES_COMMON_DEBUG_H

namespace Phyre
{
	namespace PScene
	{
		class PNode;
	} //! End of PScene Namespace
	namespace PAnimation
	{
		class PAnimationSet;
	} //! End of PAnimation Namespace

	namespace PSamplesCommon
	{
		//!
		//! Debug rendering helper functions
		//!
		void RenderClusterBounds(const PCluster &cluster, const PCamera &camera, PRendering::PRenderer &renderer);
		void RenderMeshInstanceHierarchy(const PRendering::PMeshInstance &meshInstance, const PCamera &camera, PRendering::PRenderer &renderer, bool renderBoneOrientation = false);
		void RenderMeshInstanceBoundsHierarchy(const PRendering::PMeshInstance &meshInstance, const PCamera &camera, PRendering::PRenderer &renderer);
		void RenderNodeHierarchy(PScene::PNode &node, const PCamera &camera, const PAnimation::PAnimationSet &animationSet, PRendering::PRenderer &renderer);
		void RenderLight(const PRendering::PLight &light, const PCamera &camera, float size, PRendering::PRenderer &renderer);

	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace

#endif //! PHYRE_SAMPLES_COMMON_DEBUG_H
