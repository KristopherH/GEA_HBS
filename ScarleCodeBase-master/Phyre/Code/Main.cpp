/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#include <Phyre.h>
#include <Framework/PhyreFramework.h>
#include <Rendering/PhyreRendering.h>
#include <Geometry/PhyreGeometry.h>
#include <Scene/PhyreScene.h>
#include <Serialization/PhyreSerialization.h>
#include <Text/PhyreText.h>

#include "../Common/PhyreSamplesCommon.h"
#include "../Common/PhyreSamplesCommonScene.h"
#include "Main.h"

using namespace Phyre;
using namespace PFramework;
using namespace PRendering;
using namespace PGeometry;
using namespace PSerialization;
using namespace PText;
using namespace Vectormath::Aos;
using namespace PInputs;
using namespace PSamplesCommon;

// Description:
// The maximum length for the dynamic text string.
#define PD_MAX_DYNAMIC_TEXT_LENGTH	(32)

// Description:
// The static sample application instance.
static PTextSample s_textSample;

// Description:
// The constructor for the PTextSample class.
PTextSample::PTextSample()
	: m_loadedCluster(NULL)
	, m_meshInstance(NULL)
	, m_bitmapFont(NULL)
	, m_previousDistance(0.0f)
{
	setWindowTitle("Text Sample");
	setReadmeDirectory("./Samples/Text/");

	for(PUInt32 i = 0; i < c_totalTextStrings; i++)
	{
		m_text[i] = NULL;
		m_textMaterial[i] = NULL;
	}
	
	// Register the required utilities
	PUtility::RegisterUtility(PScene::s_utilityScene);
	PUtility::RegisterUtility(PText::s_utilityText);
}

// Description:
// Initialize the scene in preparation for rendering.
// Return Value List:
// Other - The scene initialization failed.
// PE_RESULT_NO_ERROR - The scene initialization succeeded.
PResult PTextSample::initScene()
{
	// Set the current working directory to SCE_PHYRE.
	PHYRE_TRY(PhyreOS::SetCurrentDirToPhyre());

	// Load the asset file
	PHYRE_TRY(PCluster::LoadAssetFile(m_loadedCluster, "Media/" PHYRE_PLATFORM_ID "/Samples/Text/text.phyre"));
	PHYRE_TRY(FixupClusters(&m_loadedCluster, 1));

	// Add the main cluster to a world
	m_world.addCluster(*m_loadedCluster);
	
	//!
	//! Configure text rendering
	//!

	// Search for the font object in the loaded cluster
	m_bitmapFont = FindAssetRefObj<PBitmapFont>(NULL, "Samples/tuffy.fgen");
	if(!m_bitmapFont)
		return PHYRE_SET_LAST_ERROR(PE_RESULT_OBJECT_NOT_FOUND, "Unable to find bitmap font object in cluster");

	const PMaterial *textShader = FindAssetRefObj<PMaterial>(NULL, "Shaders/PhyreText");
	if (!textShader)
		return PHYRE_SET_LAST_ERROR(PE_RESULT_OBJECT_NOT_FOUND, "Unable to find text shader in cluster");

		// Create the text and text materials
	for(PUInt32 i = 0; i < c_totalTextStrings; i++)
		PHYRE_TRY(PUtilityText::CreateText(*m_bitmapFont, *m_loadedCluster, *textShader, m_text[i], m_textMaterial[i], PUtilityText::PE_TEXT_RENDER_TECHNIQUE_ALPHA_BLEND));
	
	// Configure text 0
	if(m_text[0] && m_textMaterial[0])
	{
		const PChar *text = getWindowTitle();
		PHYRE_TRY(m_text[0]->setTextLength(PhyreCheckCast<PUInt32>(strlen(text))));
		PHYRE_TRY(m_text[0]->setText(text));
		PHYRE_TRY(m_textMaterial[0]->setColor(Vector3(0.5f)));

		// Position the text in the center on the screen, near the top
		float scale  = 1.0f / (8 * m_textMaterial[0]->getBitmapFontSize());
		float height = 2.0f * m_text[0]->getTextHeight() * scale;
		float width  = 0.5f * m_text[0]->getTextWidth()  * scale;

		PMatrix4 matrix = PMatrix4::identity();
		matrix.setUpper3x3(Vectormath::Aos::Matrix3::scale(Vectormath::Aos::Vector3(scale, scale, 1.0f)));
		matrix.setTranslation(Vectormath::Aos::Vector3(-width, 1.0f - height, 1.0f));
		m_text[0]->setMatrix(matrix);
	}
	
	// Configure text 1
	if(m_text[1])
		PHYRE_TRY(m_text[1]->setText("banana.dae.phyre"));

	// Configure text 2
	if(m_text[2])
	{
		PMatrix4 matrix = PMatrix4::identity();
		float viewportScale = (float)getWidth() / (float)getHeight();

		// Since the text will be updated dynamically, we want to make sure that there should be no stalls due
		// to allocating memory or waiting for existing memory for geometry to become available.
		PHYRE_TRY(m_text[2]->setBufferCount(2));
		PHYRE_TRY(m_text[2]->setTextLength(PD_MAX_DYNAMIC_TEXT_LENGTH));

		// Position the text in the bottom left corner
		float scale = 1.0f / (12 * m_textMaterial[2]->getBitmapFontSize());
			
		matrix.setUpper3x3(Vectormath::Aos::Matrix3::scale(Vectormath::Aos::Vector3(scale, scale, 1.0f)));
		matrix.setTranslation(Vectormath::Aos::Vector3((-1.0f * viewportScale), -0.98f, 1.0f));
		m_text[2]->setMatrix(matrix);
	}
	
	//!
	//! Setup the scene camera and lights
	//!

	// Ensure the matrices are up to date before creating the camera controller
	UpdateWorldMatricesForNodes(m_world);
	PHYRE_TRY(m_cameraController.bind(m_camera));
	m_cameraController.setDistance(35.0f);

	// The scene context encapsulates information about the current scene, so add the lights from the cluster in order to light the scene
	PUInt32 lightCount = PopulateSceneContextWithLights(m_sceneContext, *m_loadedCluster, 1);
	if(!lightCount)
		PHYRE_WARN("Unable to find any lights in the asset file, your asset will be unlit\n");

	// Find a mesh instance in the cluster, use the position of the mesh instance in 3D to position the text in 2D
	m_meshInstance = FindAssetRefObj<PMeshInstance>(NULL, "Samples/banana.dae");
	if(!m_meshInstance)
		return PHYRE_SET_LAST_ERROR(PE_RESULT_OBJECT_NOT_FOUND, "Unable to find a mesh instance in the cluster");

	// Initialize gui.
	PHYRE_TRY(PImGui::Initialize(getWidth(), getHeight()));

	// Call this early to ensure we have some text to render.
	PHYRE_TRY(handleInputs());

	return PApplication::initScene();
}

// Description:
// Exit the scene in preparation for exiting the application.
// Return Value List:
// Other - The scene exit failed.
// PE_RESULT_NO_ERROR - The scene exit succeeded.
PResult PTextSample::exitScene()
{

	// Shutdown gui.
	PImGuiDebug::Terminate();
	PImGui::Terminate();

	// Free up the scene context containing the lights
	PHYRE_TRY(m_sceneContext.m_lights.resize(0));

	// Unbind the camera from the controller
	m_cameraController.unbind(m_camera);

	// Free the text objects and text materials
	for(PUInt32 i = 0; i < c_totalTextStrings; i++)
	{
		delete m_textMaterial[i];
		m_textMaterial[i] = NULL;
		delete m_text[i];
		m_text[i] = NULL;
	}
	
	// Free the loaded cluster
	delete m_loadedCluster;
	
	return PApplication::exitScene();
}

// Description:
// Handle user inputs.
// Return Value List:
// PE_RESULT_NO_ERROR - The inputs were handled successfully.
// Other - An error occurred whilst handling inputs.
PResult PTextSample::handleInputs()
{
	// Handle gui.
	if (checkAndClearKey(PInputBase::InputChannel_Key_Y) || checkAndClearJoypadButton(PInputBase::InputChannel_Button_Start))
		m_showImGui = !m_showImGui;
	// Handle camera transformations
	updateCamera(m_cameraController, (float)m_elapsedTime);

	m_camera.updateViewMatrices();

	m_cameraController.setDistance(PhyreClamp(m_cameraController.getDistance(), 0.0f, 500.0f));

	PMatrix4 matrix = PMatrix4::identity();
	float viewportScale = (float)getWidth() / (float)getHeight();

	if(m_text[1] && m_textMaterial[1])
	{
		// Configure the position of text 1
		PMatrix4 localToWorld = PMatrix4(m_meshInstance->getLocalToWorldMatrix()->getMatrix());
		Vector4 position = m_camera.getViewProjectionMatrix() * Point3(localToWorld.getTranslation());
		Vector3 screenPosition = position.getXYZ() / position.getW();
		screenPosition.setZ(1.0f);

		float scale  = 1.0f / ((m_cameraController.getDistance() / 4) * m_textMaterial[1]->getBitmapFontSize());
		float width  = 0.5f * m_text[1]->getTextWidth() * scale;
		
		matrix.setUpper3x3(Vectormath::Aos::Matrix3::scale(Vectormath::Aos::Vector3(scale, scale, 1.0f)));
		matrix.setTranslation(Vectormath::Aos::Vector3((screenPosition.getX() * viewportScale) - width, screenPosition.getY(), 1.0f));
		m_text[1]->setMatrix(matrix);
	}

	if(m_text[2] && m_textMaterial[2])
	{
		// Configure the text 2 string and its position
		float currentDistance = m_cameraController.getDistance();
		if(currentDistance != m_previousDistance)
		{
			PChar distanceString[PD_MAX_DYNAMIC_TEXT_LENGTH];
			PHYRE_SNPRINTF(distanceString, PHYRE_STATIC_ARRAY_SIZE(distanceString), "Camera distance: %.2f", currentDistance);
			PHYRE_TRY(m_text[2]->setText(distanceString));

			// Update the previous distance
			m_previousDistance = currentDistance;
		}
	}

	return PApplication::handleInputs();
}

// Description:
// Informs the application that the window has been resized.
// Return Value List:
// PE_RESULT_NO_ERROR - The application resized successfully.
// Other - The application did not resize successfully.
PResult PTextSample::resize()
{
	PResult success = PApplication::resize();

	// Forcibly change the distance value to trigger the text matrix to be updated taking into account the new window size
	m_previousDistance = FLT_MAX;

	// Reconfigure the position of the dynamic text due to window resize
	if(m_text[2])
	{
		PMatrix4 matrix = PMatrix4::identity();
		float viewportScale = (float)getWidth() / (float)getHeight();

		// Position the text in the bottom left corner
		float scale = 1.0f / (12 * m_textMaterial[2]->getBitmapFontSize());
			
		matrix.setUpper3x3(Vectormath::Aos::Matrix3::scale(Vectormath::Aos::Vector3(scale, scale, 1.0f)));
		matrix.setTranslation(Vectormath::Aos::Vector3((-1.0f * viewportScale), -0.98f, 1.0f));
		m_text[2]->setMatrix(matrix);
	}

	return success;
}

// Description:
// Render method.
// Return Value list:
// PE_RESULT_NO_ERROR - The render operation completed successfully.
// Other - An error occurred whilst rendering the scene.
PResult PTextSample::render()
{
	UpdateWorldMatricesForNodes(m_world);

	m_camera.setAspect((float)(getWidth()) / (float)(getHeight()));
	m_camera.updateViewMatrices();

	// Tell the renderer which camera we want to use for rendering
	m_renderer.setCamera(m_camera);
	PHYRE_TRY(m_renderer.setClearColor(0.1f, 0.1f, 0.8f, 0.5f));
	PHYRE_TRY(m_renderer.beginScene(PRenderInterfaceBase::PE_CLEAR_COLOR_BUFFER_BIT | PRenderInterfaceBase::PE_CLEAR_DEPTH_BUFFER_BIT));
	
	// Iterate through all mesh instances in the cluster and render them for the Opaque render pass
	m_renderer.setSceneRenderPassType(PHYRE_GET_SCENE_RENDER_PASS_TYPE(Opaque));
	//renderWorld(m_world, m_camera);

	// Render the text objects
	for(PUInt32 i = 0; i < c_totalTextStrings; i++)
	{
		if(m_text[i])
			PHYRE_TRY(m_text[i]->renderText(m_renderer));
	}
	PHYRE_TRY(m_renderer.endScene());

	// Render sample gui.
	PImGui::RenderGui(m_renderer, *this);

	return PE_RESULT_NO_ERROR;
}
