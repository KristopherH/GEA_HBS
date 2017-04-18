﻿/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef TEXT_H
#define TEXT_H

// Description:
// Sample application definition.
class PTextSample : public Phyre::PFramework::PApplication
{
protected:
	// Phyre Framework overrides
	virtual Phyre::PResult initScene();
	virtual Phyre::PResult exitScene();
	virtual Phyre::PResult handleInputs();
	virtual Phyre::PResult render();
	virtual Phyre::PResult resize();

	static const Phyre::PUInt32 c_totalTextStrings = 3;									// The number of text strings used by this sample.
	
	Phyre::PCluster								*m_loadedCluster;						// The loaded cluster containing the assets.
	Phyre::PRendering::PMeshInstance			*m_meshInstance;						// A pointer to the mesh instance for the loaded cluster.
	
	Phyre::PText::PBitmapFont					*m_bitmapFont;							// The bitmap font object.
	Phyre::PText::PBitmapTextMaterial			*m_textMaterial[c_totalTextStrings];	// The material used to render the text with.
	Phyre::PText::PBitmapFontText				*m_text[c_totalTextStrings];			// The text object to be rendered.

	Phyre::PCameraPerspective					m_camera;								// The camera to be used for rendering the scene.
	Phyre::PWorldMatrixOrbitController			m_cameraController;						// The camera controller used to orientate the camera within the scene.

	float										m_previousDistance;						// The previous camera distance.

public:
	PTextSample();
};

#endif //! TEXT_H
