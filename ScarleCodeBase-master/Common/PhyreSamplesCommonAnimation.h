/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef PHYRE_SAMPLES_COMMON_ANIMATION_H
#define PHYRE_SAMPLES_COMMON_ANIMATION_H

#include <Animation/PhyreAnimation.h>

namespace Phyre
{
	namespace PSamplesCommon
	{
		//!
		//! Animation helper functions
		//!
		PAnimation::PAnimationNetworkInstance *CreateAnimationForClip(PCluster &cluster, PAnimation::PAnimationSet &animSet, PAnimation::PAnimationClip &clip, PArray<PAnimation::PAnimationSlotArrayElement> &animationProcessBuffer);
		PAnimation::PAnimationNetworkInstance *CreateAnimation(PCluster &cluster, PArray<PAnimation::PAnimationSlotArrayElement> &animationProcessBuffer);
		PHYRE_DEPRECATED(void UpdateAnimations(float elapsedTime, PAnimation::PAnimationNetworkInstance &animationNetworkInstance), "Deprecated in 3.17.0.0: Please add animation network instances to the world and allow PFrameworkApplication to process them.");
	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace

#endif //! PHYRE_SAMPLES_COMMON_ANIMATION_H
