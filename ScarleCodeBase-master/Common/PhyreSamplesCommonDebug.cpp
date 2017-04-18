/* SIE CONFIDENTIAL
PhyreEngine(TM) Package 3.17.0.0
* Copyright (C) 2016 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#include <Phyre.h>
#include <Rendering/PhyreRendering.h>
#include <Scene/PhyreScene.h>
#include <Animation/PhyreAnimation.h>

using namespace Vectormath::Aos;

namespace Phyre
{
	namespace PSamplesCommon
	{
		//!
		//! Render bounds
		//!

		// Description:
		// Renders the bounds for mesh instances in a cluster.
		// Arguments:
		// cluster : The cluster containing bounds for mesh instances to be rendered.
		// camera : The camera to be used for rendering.
		// renderer : The renderer to be used for rendering.
		void RenderClusterBounds(const PCluster &cluster, const PCamera &camera, PRendering::PRenderer &renderer)
		{
			for(PCluster::PConstObjectIteratorOfType<PRendering::PMeshInstanceBounds> boundsIt(cluster); boundsIt; ++boundsIt)
				boundsIt->debugDrawBounds(renderer, camera);			
		}

		//!
		//! Render animation hierarchy using the mesh instance
		//!

		// Description:
		// The PHierarchyRenderData class stores information for rendering the hierarchy in a PMeshInstance object.
		class PMeshInstanceHierarchyRenderData
		{
			PHYRE_PRIVATE_ASSIGNMENT_OPERATOR(PMeshInstanceHierarchyRenderData);
		public:
			Matrix4							m_viewProjection;			// The matrix to be used to render the hierarchy.
			const PRendering::PMeshInstance	&m_meshInstance;			// The mesh instance hierarchy to be rendered.
			bool							m_renderBoneOrientation;	// A flag that indicates whether the orientation of the bone should be rendered.

			// Description:
			// The constructor for the PMeshInstanceHierarchyRenderData class.
			// Gets the view projection matrix from the camera and sets the mesh instance to be rendered.
			// Arguments:
			// meshInstance : The mesh instance hierarchy to be rendered.
			// camera : The camera to be used to render the mesh instance hierarchy.
			// renderBoneOrientation : A flag that indicates whether the orientation of the bone should be rendered.
			PMeshInstanceHierarchyRenderData(const PRendering::PMeshInstance &meshInstance, const PCamera &camera, bool renderBoneOrientation)
				: m_viewProjection(camera.getViewProjectionMatrix())
				, m_meshInstance(meshInstance)
				, m_renderBoneOrientation(renderBoneOrientation)
			{
			}
		};

		// Description:
		// A callback method to render a mesh instance hierarchy using the debug draw API.
		// Arguments:
		// data :  The render callback data.                                
		void RenderMeshInstanceHierarchyCallback(const PRendering::PRenderCallbackData &data)
		{
			PRendering::PRenderInterface		&renderInterface		= data.m_renderInterface;
			PMeshInstanceHierarchyRenderData	*hierarchyRenderData	= static_cast<PMeshInstanceHierarchyRenderData *>(data.m_userData);
			const Matrix4						&viewProjection			= hierarchyRenderData->m_viewProjection;
			const PRendering::PMeshInstance		&meshInstance			= hierarchyRenderData->m_meshInstance;

			// Collapse the matrix hierarchy for the segments in the mesh instance.
			const PGeometry::PMesh	&mesh					= meshInstance.getMesh();
			PUInt32					matrixCount				= mesh.getHierarchyMatrixCount();
			if(!matrixCount)
				return;

			const PInt32		*parentIndices	= mesh.getMatrixParentIndices();
			PArray<PMatrix4>	globalMatricesArray(matrixCount +1);
			PMatrix4			*globalMatrices	= globalMatricesArray.getArray();
			if(!globalMatrices)
				return;
			globalMatrices++;
			meshInstance.buildGlobalMeshInstanceMatrixHierarchy(globalMatrices);

			Vector4 *points = (Vector4 *)alloca(matrixCount * 2 * sizeof(Vector4));
			Vector4 *point = points;
			Vectormath::Aos::Vector4 red(1.0f, 0.0f, 0.0f, 1.0f);
			Vectormath::Aos::Vector4 yellow(1.0f, 1.0f, 0.0f, 1.0f);
			Vectormath::Aos::Vector4 blue(0.0f, 0.0f, 1.0f, 1.0f);
			Vectormath::Aos::Vector4 white(1.0f, 1.0f, 1.0f, 1.0f);
			for (PUInt32 matrixIndex = 0; matrixIndex < matrixCount; matrixIndex++, parentIndices++)
			{
				PInt32 parent = *parentIndices;
				if(parent >= 0)
				{
					*point++ = Vector4(globalMatrices[parent].getTranslation(), 1.0f);
					*point++ = Vector4(globalMatrices[matrixIndex].getTranslation(), 1.0f);
				}

				if (hierarchyRenderData->m_renderBoneOrientation)
				{
					PMatrix4 bone = globalMatrices[matrixIndex];
					Vectormath::Aos::Vector4 bonePoints[4];
					bonePoints[0] = Vectormath::Aos::Vector4(bone.getTranslation(), 1.0f);
					
					const float widgetsize = 0.025f;
					bonePoints[1] = bonePoints[0] + (bone.getCol0() * widgetsize);
					bonePoints[2] = bonePoints[0] + (bone.getCol1() * widgetsize);
					bonePoints[3] = bonePoints[0] + (bone.getCol2() * widgetsize);

					PUInt32 indices[6] = { 0, 1, 0, 2, 0, 3 };
					renderInterface.debugDraw(PGeometry::PE_PRIMITIVE_LINES, bonePoints, red   , indices + 0, 2, &viewProjection);
					renderInterface.debugDraw(PGeometry::PE_PRIMITIVE_LINES, bonePoints, yellow, indices + 2, 2, &viewProjection);
					renderInterface.debugDraw(PGeometry::PE_PRIMITIVE_LINES, bonePoints, blue  , indices + 4, 2, &viewProjection);
				}
			}

			renderInterface.debugDraw(PGeometry::PE_PRIMITIVE_LINES, points, white, NULL, (PUInt32) (point - points), &viewProjection);
		}

		// Description:
		// Adds a callback to render the hierarchy of the specified mesh instance.
		// Arguments:
		// meshInstance : The mesh instance to render.
		// camera :    The camera.
		// renderer :  The renderer to add this render call to.
		// renderBoneOrientation : A flag that indicates whether the orientation of the bone should be rendered. Defaults to false.
		void RenderMeshInstanceHierarchy(const PRendering::PMeshInstance &meshInstance, const PCamera &camera, PRendering::PRenderer &renderer, bool renderBoneOrientation /* = false */)
		{
			void *userData = NULL;
			renderer.addRenderCallbackWithAllocatedBuffer(RenderMeshInstanceHierarchyCallback, sizeof(PMeshInstanceHierarchyRenderData), userData);
			if(userData)
				new(userData)PMeshInstanceHierarchyRenderData(meshInstance, camera, renderBoneOrientation);
		}

		// Description:
		// A callback method to render a mesh instance bounds hierarchy using the debug draw API.
		// Arguments:
		// data :  The render callback data.                                
		void RenderMeshInstanceBoundsHierarchyCallback(const PRendering::PRenderCallbackData &data)
		{
			using namespace PGeometry;

			PRendering::PRenderInterface		&renderInterface		= data.m_renderInterface;
			PMeshInstanceHierarchyRenderData	*hierarchyRenderData	= static_cast<PMeshInstanceHierarchyRenderData *>(data.m_userData);
			const Matrix4						&viewProjection			= hierarchyRenderData->m_viewProjection;
			const PRendering::PMeshInstance		&meshInstance			= hierarchyRenderData->m_meshInstance;

			// Collapse the matrix hierarchy for the segments in the mesh instance.
			const PMesh					&mesh		= meshInstance.getMesh();
			const PSkeletonJointBounds *bounds		= mesh.getSkeletonBounds();
			PUInt32						matrixCount	= mesh.getHierarchyMatrixCount();
			PUInt32						jointCount	= mesh.getSkeletonMatrixCount();
			if(!matrixCount || !bounds)
				return;

			PArray<PMatrix4>	globalMatricesArray(matrixCount +1);
			PMatrix4			*globalMatrices = globalMatricesArray.getArray();
			if(!globalMatrices)
				return;
			globalMatrices++;
			meshInstance.buildGlobalMeshInstanceMatrixHierarchy(globalMatrices);

			PUInt32			indexCount	= jointCount * 24;
			PArray<Vector4> pointsArray(jointCount * 8);
			PArray<PUInt32> indicesArray(indexCount);
			Vector4 		*points		= pointsArray.getArray();
			PUInt32 		*indices	= indicesArray.getArray();
			if(!points || !indices)
				return;

			// Build the indices for each box
			static PUInt32 s_boxIndices[24] = {
				0, 4,	0, 2,	0, 1,	7, 3,	7, 5,	7, 6,
				4, 6,	4, 5,	2, 6,	2, 3,	1, 5,	1, 3 };
			PUInt32 jointIndexBase = 0;
			for (PUInt32 jointIndex = 0; jointIndex < jointCount; jointIndex++, jointIndexBase += 8)
				for(PUInt32 i = 0 ; i < 24 ; i++)
					*indices++ = jointIndexBase + s_boxIndices[i];

			// Create the points
			// Use the segments since they map skeleton to hierarchy
			for (PUInt32 jointIndex = 0; jointIndex < jointCount; jointIndex++, bounds++)
			{
				const PMatrix4	&globalMatrixForJoint	= globalMatrices[bounds->getHierarchyMatrixIndex()];
				Point3			boundsPoints[8];
				PRendering::PMeshInstanceBounds::GetBoundsPoints(bounds->getMin(), bounds->getMin() + bounds->getSize(), boundsPoints);
				for(PUInt32 j = 0 ; j < 8 ; j++)
					*points++ = Vector4(globalMatrixForJoint * boundsPoints[j]);
			}

			Vector4 color(0.0f, 1.0f, 0.0f, 1.0f);
			renderInterface.debugDraw(PGeometry::PE_PRIMITIVE_LINES, pointsArray.getArray(), color, indicesArray.getArray(), indexCount, &viewProjection);
		}

		// Description:
		// Adds a callback to render the bounds of the hierarchy of the specified mesh instance.
		// Arguments:
		// meshInstance : The mesh instance to render.
		// camera :    The camera.
		// renderer :  The renderer to add the bounds to.
		void RenderMeshInstanceBoundsHierarchy(const PRendering::PMeshInstance &meshInstance, const PCamera &camera, PRendering::PRenderer &renderer)
		{
			void *userData = NULL;
			renderer.addRenderCallbackWithAllocatedBuffer(RenderMeshInstanceBoundsHierarchyCallback, sizeof(PMeshInstanceHierarchyRenderData), userData);
			if(userData)
				new(userData) PMeshInstanceHierarchyRenderData(meshInstance, camera, false);
		}

		//!
		//! Render animation hierarchy using the node
		//!

		// Description:
		// The PHierarchyRenderData class stores information for rendering the hierarchy in a PNode object.
		class PNodeHierarchyRenderData
		{
			PHYRE_PRIVATE_ASSIGNMENT_OPERATOR(PNodeHierarchyRenderData);
		public:
			Matrix4		m_viewProjection;	// The matrix to be used to render the hierarchy.
			PScene::PNode					&m_node;			// The node to render from.
			const PAnimation::PAnimationSet &m_animationSet;	// The animation set.

			// Description:
			// The constructor for the PNodeHierarchyRenderData class.
			// Gets the view projection matrix from the camera and sets the mesh instance to be rendered.
			// Arguments:
			// node : The node hierarchy to be rendered.
			// camera : The camera to be used to render the mesh instance hierarchy.
			// animationSet : The animation set.
			PNodeHierarchyRenderData(PScene::PNode &node, const PCamera &camera, const PAnimation::PAnimationSet &animationSet)
				: m_viewProjection(camera.getViewProjectionMatrix())
				, m_node(node)
				, m_animationSet(animationSet)
			{
			}
		};

		// Description:
		// A callback method to render a node hierarchy using the debug draw API.
		// Arguments:
		// data :  The render callback data.                                
		void RenderNodeHierarchyCallback(const PRendering::PRenderCallbackData &data)
		{
			PRendering::PRenderInterface	&renderInterface		= data.m_renderInterface;
			PNodeHierarchyRenderData		*hierarchyRenderData	= static_cast<PNodeHierarchyRenderData *>(data.m_userData);
			const Matrix4	&viewProjection			= hierarchyRenderData->m_viewProjection;
			PScene::PNode					&node					= hierarchyRenderData->m_node;
			const PAnimation::PAnimationSet	&animationSet			= hierarchyRenderData->m_animationSet;
			
			PUInt32 targetCount = animationSet.getTargetCount();
			if (targetCount)
			{
				const PAnimation::PAnimationChannelTarget *targets = animationSet.getTarget(0);
				if (!targets)
					return;

				// Find all the nicknamed nodes in one traversal
				const PChar **nicknames = (const PChar **)alloca(targetCount * sizeof(PChar *));

				// Capture names for PNodes.
				PUInt32 i;
				for (i=0; i<targetCount; i++)
				{
					const PAnimation::PAnimationChannelTarget &target = targets[i];
					const PClassDescriptor &cd = target.getTargetObjectType();
					const PChar *nickname = NULL;
					if ((target.getTargetType() == PAnimation::PAnimationChannelTarget::PE_TARGETTYPE_NAMED_OBJECT) && (cd.isTypeOf(PHYRE_CLASS(PScene::PNode))))
						nickname = targets[i].getTargetName();
					nicknames[i] = nickname;
				}

				PScene::PNode **nodes = (PScene::PNode **)alloca(targetCount * sizeof(PScene::PNode *));
				memset(nodes, 0, sizeof(nodes[0]) * targetCount);

				PAnimation::PVisitorFindNicknamedNodes findNicknamedNodes(node);
				findNicknamedNodes.findNodes(nicknames, nodes, targetCount);

				Vector4 color(1.0f);
				Vector4 points[2];
				for (i=0; i<targetCount; i++)
				{
					if (nodes[i])
					{
						PMatrix4 wm	= nodes[i]->calculateWorldMatrix();
						points[0] = Vector4(wm.getTranslation(), 1.0f);
						for(PScene::PNode *child = nodes[i]->getFirstChild() ; child ; child = child->getNextSibling())
						{
							PMatrix4 wmc = child->calculateWorldMatrix();
							points[1] = Vector4(wmc.getTranslation(), 1.0f);
							renderInterface.debugDraw(PGeometry::PE_PRIMITIVE_LINES, points, color, NULL, 2, &viewProjection);
						}
					}
				}
			}
		}

		// Description:
		// Adds a callback to render the hierarchy of the specified node.
		// Arguments:
		// node : The node to render.
		// camera :    The camera.
		// animationSet : The animation set.
		// renderer :  The renderer to add this bound box to.
		void RenderNodeHierarchy(PScene::PNode &node, const PCamera &camera, const PAnimation::PAnimationSet &animationSet, PRendering::PRenderer &renderer)
		{
			void *userData = NULL;
			renderer.addRenderCallbackWithAllocatedBuffer(RenderNodeHierarchyCallback, sizeof(PNodeHierarchyRenderData), userData);
			if(userData)
				new(userData) PNodeHierarchyRenderData(node, camera, animationSet);
		}

		//!
		//! Render light
		//!

		// Description:
		// Class holding data for rendering light visualizations.
		class PLightRenderData
		{
			PHYRE_PRIVATE_ASSIGNMENT_OPERATOR(PLightRenderData);
		public:
			Matrix4 m_viewProjection;			// The camera's view projection matrix.
			PMatrix4 m_lightMatrix;				// The light's local to world matrix.
			Vector3 m_cameraPos;				// The camera's world position.
			const PRendering::PLight &m_light;	// The light for which to render a visualization.
			float m_size;						// The size to render the light.

			// Description:
			// The constructor for the PLightRenderData class.
			// Arguments:
			// light - The light to render.
			// camera - The camera through which to render the light.
			// size - The size of the visualization to render.
			PLightRenderData(const PRendering::PLight &light, const PCamera &camera, float size)
				: m_viewProjection(camera.getViewProjectionMatrix())
				, m_lightMatrix(light.getLocalToWorldMatrix() ? PMatrix4(light.getLocalToWorldMatrix()->getMatrix()) : PMatrix4::Identity())
				, m_cameraPos(camera.getLocalToWorldMatrix() ? camera.getLocalToWorldMatrix()->getMatrix().getTranslation() : Vector3(0,0,0))
				, m_light(light)
				, m_size(size)
			{
			}
		};
		
		// Description:
		// The vertex array class allows pre-allocation of vertex data to avoid copying data around as the array grows.
		class PVertexArray : public PArray<Vector4>
		{
		protected:
			PUInt32 m_filledCount;								// The number of vertices that have been filled.

		public:

			// Description:
			// The constructor for the PVertexArray class.
			PVertexArray()
				: m_filledCount(0)
			{
			}

			// Description:
			// Reserves some more vertices.
			// Arguments:
			// count - The number of vertices to reserve.
			// Return Value List:
			// PE_RESULT_NO_ERROR - The requested number of vertices have been reserved.
			// PE_RESULT_OUT_OF_MEMORY - There was insufficient memory to reserve the requested number of vertices.
			PResult reserve(PUInt32 count)
			{
				PUInt32 newCount = PArray<Vector4>::getCount() + count;
				return resizeWithPreserve(newCount);
			}

			// Description:
			// Add a vector to the vertex array.
			// Arguments:
			// v - The vector to add.
			// Return Value List:
			// PE_RESULT_NO_ERROR - The vector has been added successfully.
			// PE_RESULT_OUT_OF_MEMORY - There was insufficient memory to add the vector.
			PResult add(const Vector4 &v)
			{
				if ((m_filledCount+1) > PArray<Vector4>::getCount())
				{
					PHYRE_TRY(reserve(1));
				}

				(*this)[m_filledCount++] = v;
				return PE_RESULT_NO_ERROR;
			}

			// Description:
			// Get the number of vertices added.
			// Returns:
			// The number of vertices added.
			PUInt32 getCount()
			{
				return m_filledCount;
			}

			// Description:
			// Add a line (as 2 points) to the vertex array.
			// Arguments:
			// v1 - The first vertex of the line.
			// v2 - The second vertex of the line.
			// Return Value List:
			// PE_RESULT_NO_ERROR - The vector has been added successfully.
			// PE_RESULT_OUT_OF_MEMORY - There was insufficient memory to add the vector.
			PResult addLine(const Vector3 &v1, const Vector3 &v2)
			{
				if ((m_filledCount+2) > PArray<Vector4>::getCount())
				{
					PHYRE_TRY(reserve(2));
				}

				(*this)[m_filledCount++] = Vector4(v1, 1.0f);
				(*this)[m_filledCount++] = Vector4(v2, 1.0f);
				return PE_RESULT_NO_ERROR;
			}
		};

		// Description:
		// Add an arrow to the vertex buffer. For positive size values the arrow points down the negative Z axis.
		// Arguments:
		// vertices - The vertex buffer to which to add the arrow.
		// axisValid - The axis supplied for rotating the arrow wings is valid.
		// axis - The axis with which to rotate the arrow wings.
		// size - The size of the arrow to add.
		// Return Value List:
		// PE_RESULT_NO_ERROR - The vertices were added successfully.
		// PE_RESULT_OUT_OF_MEMORY - There was insufficient memory to add the vertices.
		static PResult AddArrow(PVertexArray &vertices, bool axisValid, const Vector3 &axis, float size)
		{
			Vector3 arrowStart(0,0,0);
			Vector3 arrowEnd(0, 0, -size);

			PHYRE_TRY(vertices.addLine(arrowStart, arrowEnd));

			if (axisValid)
			{
				// Draw edges rotated at +/- 0.5 radians in the view plane.
				Matrix3 rot1 = Matrix3::rotation( 0.5f, axis);
				Matrix3 rot2 = Matrix3::rotation(-0.5f, axis);

				Vector3 corner1 = rot1 * arrowEnd;
				Vector3 corner2 = rot2 * arrowEnd;

				PHYRE_TRY(vertices.addLine(arrowEnd, corner1));
				PHYRE_TRY(vertices.addLine(arrowEnd, corner2));
			}

			return PE_RESULT_NO_ERROR;
		}

		// Description:
		// A callback method to render a light using the debug draw API.
		// Arguments:
		// data :  The render callback data.                                
		void RenderLightCallback(const PRendering::PRenderCallbackData &data)
		{
			PRendering::PRenderInterface &ri = data.m_renderInterface;
			const PLightRenderData *visData = (const PLightRenderData *)data.m_userData;
			if (visData)
			{
				const PRendering::PLight &light = visData->m_light;
				const Matrix4 &viewProj = visData->m_viewProjection;
				const PMatrix4 &mtx = visData->m_lightMatrix;
				const Vector3 &cameraPos = visData->m_cameraPos;
				float size = visData->m_size;

				const PRendering::PLightType *lightType = light.getLightType();
				Vector4 color = Vector4(light.getColor().getXYZ(), 1.0f);

				Vector3 cameraToLight = normalize(mtx.getTranslation() - cameraPos);

				// Generate a light perpendicular in the view plane.
				// Backtransform the camera->light vector into light space.
				Vector3 cameraToLightLS = normalize(inverse(mtx) * cameraToLight);

				bool perpValid = fabsf(cameraToLightLS.getZ()) < 0.999f;

				// Generate vector perpendicular to view and light "at" vector by cross product 
				Vector3 perp = normalize(cross(cameraToLightLS, Vector3(0,0,1)));
				Vector3 axis = normalize(cross(perp, Vector3(0,0,1)));

				PVertexArray vertices;

				if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::DirectionalLight))
				{
					// Render a directional light as a arrow pointing down negative Z axis.
					vertices.reserve(6);
					AddArrow(vertices, perpValid, axis, size);
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::SpotLight))
				{
					const PUInt32 c_subdivs = 20;

					// Render a spot light as two cones pointing down negative Z axis.
					float angle[2] = {light.getInnerConeAngle(),		// Inner half angle in radians.
										light.getOuterConeAngle()};		// Outer half angle in radians.

					vertices.reserve(4*2 + c_subdivs*2*2);

					if (perpValid)
					{
						// Draw edges
						for (PUInt32 i=0; i<2; i++)
						{
							float halfAngle = angle[i];

							Matrix3 rot1 = Matrix3::rotation( halfAngle, axis);			// Rotate light "at" vector to cone edge.
							Matrix3 rot2 = Matrix3::rotation(-halfAngle, axis);			// Rotate light "at" vector to cone edge.

							Vector3 corner1 = rot1 * Vector3(0,0,size);
							Vector3 corner2 = rot2 * Vector3(0,0,size);
							vertices.addLine(Vector3(0, 0, 0), -corner1);
							vertices.addLine(Vector3(0, 0, 0), -corner2);
						}
					}

					// Draw circles.
					for (PUInt32 i=0; i<2; i++)
					{
						float halfAngle = angle[i];
						float cosHalfAngle = cosf(halfAngle) * size;
						float sinHalfAngle = sinf(halfAngle) * size;

						for (PUInt32 j=0; j<c_subdivs; j++)
						{
							const float c_pi = 3.1415926535897932f;
							float theta1 = (2*c_pi) * ((float)j/(float)c_subdivs);
							float theta2 = (2*c_pi) * ((float)(j+1)/(float)c_subdivs);

							float x1 = sinf(theta1) * sinHalfAngle;
							float y1 = cosf(theta1) * sinHalfAngle;
							float x2 = sinf(theta2) * sinHalfAngle;
							float y2 = cosf(theta2) * sinHalfAngle;

							vertices.addLine(-Vector3(x1, y1, cosHalfAngle), -Vector3(x2, y2, cosHalfAngle));
						}
					}
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::PointLight))
				{
					vertices.reserve(6);

					// Render a point light as a cross.
					vertices.addLine(Vector3(-size,0,0), Vector3(size,0,0));
					vertices.addLine(Vector3(0,-size,0), Vector3(0,size,0));
					vertices.addLine(Vector3(0,0,-size), Vector3(0,0,size));
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::AreaDiscLight))
				{
					const PUInt32 c_subdivs = 20;

					vertices.reserve(6 + c_subdivs*2);

					// Render area disc light as circle with arrow.
					AddArrow(vertices, perpValid, axis, size);

					float r = light.getAreaRadius();

					for (PUInt32 j=0; j<c_subdivs; j++)
					{
						const float c_pi = 3.1415926535897932f;
						float theta1 = (2.0f*c_pi) * ((float)j/(float)c_subdivs);
						float theta2 = (2.0f*c_pi) * ((float)(j+1)/(float)c_subdivs);

						float x1 = sinf(theta1) * r;
						float y1 = cosf(theta1) * r;
						float x2 = sinf(theta2) * r;
						float y2 = cosf(theta2) * r;

						vertices.addLine(Vector3(x1, y1, 0), Vector3(x2, y2, 0));
					}

				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::AreaSphereLight))
				{
					const PUInt32 c_subdivs = 20;

					vertices.reserve(c_subdivs * 6);

					float r = light.getAreaRadius();

					for (PUInt32 j=0; j<c_subdivs; j++)
					{
						const float c_pi = 3.1415926535897932f;
						float theta1 = (2.0f*c_pi) * ((float)j/(float)c_subdivs);
						float theta2 = (2.0f*c_pi) * ((float)(j+1)/(float)c_subdivs);

						float x1 = sinf(theta1) * r;
						float y1 = cosf(theta1) * r;
						float x2 = sinf(theta2) * r;
						float y2 = cosf(theta2) * r;

						vertices.addLine(Vector3(x1, y1, 0), Vector3(x2, y2, 0));
						vertices.addLine(Vector3(0, x1, y1), Vector3(0, x2, y2));
						vertices.addLine(Vector3(x1, 0, y1), Vector3(x2, 0, y2));
					}
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::AreaRectangleLight))
				{
					vertices.reserve(6 + 8);

					// Render area rectangle light as rectangle with arrow.
					AddArrow(vertices, perpValid, axis, size);

					float hw = light.getAreaHalfWidth();
					float hh = light.getAreaHalfHeight();

					vertices.addLine(Vector3(-hw, -hh, 0), Vector3( hw, -hh, 0));
					vertices.addLine(Vector3(-hw,  hh, 0), Vector3( hw,  hh, 0));
					vertices.addLine(Vector3(-hw, -hh, 0), Vector3(-hw,  hh, 0));
					vertices.addLine(Vector3( hw, -hh, 0), Vector3( hw,  hh, 0));
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::AreaTubeLight))
				{
					const PUInt32 c_subdivs = 10;

					vertices.reserve(c_subdivs * (2 + c_subdivs*4));

					// Render area tube light as capsule with arrow.
					float hw = light.getAreaHalfWidth();
					float r = light.getAreaRadius();

					for (PUInt32 j=0; j<c_subdivs; j++)
					{
						const float c_pi = 3.1415926535897932f;
						float theta = (2*c_pi) * ((float)j/(float)c_subdivs);
					
						float y = sinf(theta) * r;
						float z = cosf(theta) * r;

						Vector3 start(-hw, y, z);
						Vector3 end(hw, y, z);
					
						vertices.addLine(start, end);

						for (PUInt32 k=0; k<c_subdivs; k++)
						{
							float theta1 = (c_pi/2) * ((float)k/(float)c_subdivs);
							float theta2 = (c_pi/2) * ((float)(k+1)/(float)c_subdivs);

							float cosTheta1 = cos(theta1);
							float sinTheta1 = sin(theta1);
							float cosTheta2 = cos(theta2);
							float sinTheta2 = sin(theta2);

							Vector3 p1(-hw-sinTheta1*r, y*cosTheta1, z*cosTheta1);
							Vector3 p2(-hw-sinTheta2*r, y*cosTheta2, z*cosTheta2);
							vertices.addLine(p1, p2);
							Vector3 p3( hw+sinTheta1*r, y*cosTheta1, z*cosTheta1);
							Vector3 p4( hw+sinTheta2*r, y*cosTheta2, z*cosTheta2);
							vertices.addLine(p3, p4);
						}
					}
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::GlobalLightProbe))
				{
					// No visualization of global light probes.
				}
				else if (lightType == PHYRE_GET_LIGHT_TYPE(PRendering::LocalLightProbe))
				{
					float radius = light.getAreaRadius();
					if (radius > 0.0f)
					{
						// It's a spherical local light probe.
						const PUInt32 c_subdivs = 20;

						vertices.reserve(c_subdivs * 6);

						// Render local light probe as cross and sphere at probe location.
						float r = light.getAreaRadius();

						for (PUInt32 j=0; j<c_subdivs; j++)
						{
							const float c_pi = 3.1415926535897932f;
							float theta1 = (2.0f*c_pi) * ((float)j/(float)c_subdivs);
							float theta2 = (2.0f*c_pi) * ((float)(j+1)/(float)c_subdivs);

							float x1 = sinf(theta1) * r;
							float y1 = cosf(theta1) * r;
							float x2 = sinf(theta2) * r;
							float y2 = cosf(theta2) * r;

							vertices.addLine(Vector3(x1, y1, 0), Vector3(x2, y2, 0));
							vertices.addLine(Vector3(0, x1, y1), Vector3(0, x2, y2));
							vertices.addLine(Vector3(x1, 0, y1), Vector3(x2, 0, y2));
						}
					}
					else
					{
						// It's a box local light probe. Render the box.
						Vector3 pts[8];
						for (PUInt32 i=0; i<PHYRE_STATIC_ARRAY_SIZE(pts); i++)
						{
							float x = i&1 ? 1.0f : -1.0f;
							float y = i&2 ? 1.0f : -1.0f;
							float z = i&4 ? 1.0f : -1.0f;
							pts[i] = Vector3(x*light.getAreaHalfWidth(), y*light.getAreaHalfHeight(), z*light.getAreaHalfDepth());
						}

						//	  6-----7
						//	 /|    /|
						//	/ |   / |
						// 2-----3	|
						// |  4--|--5
						// | /   | /
						// |/    |/
						// 0-----1	

						static const PUInt8 s_lineVertIndices[][2] = {
							{0, 1}, {1, 3}, {3, 2}, {2, 0},				// Front face edges.
							{4, 5}, {5, 7}, {7, 6}, {6, 4},				// Back face edges.
							{0, 4}, {1, 5}, {2, 6}, {4, 7},				// Front to back edges.
							{0, 3}, {1, 2},								// Front face cross.
							{4, 7}, {5, 6},								// Back face cross.
							{0, 6}, {2, 4},								// Left face cross.
							{2, 7}, {3, 6},								// Top face cross.
							{1, 7}, {3, 5},								// Right face cross.
							{0, 5}, {1, 4}								// Bottom face cross.
						};

						vertices.reserve(PHYRE_STATIC_ARRAY_SIZE(s_lineVertIndices) * 2);

						for (PUInt32 i=0; i<PHYRE_STATIC_ARRAY_SIZE(s_lineVertIndices); i++)
							vertices.addLine(pts[s_lineVertIndices[i][0]], pts[s_lineVertIndices[i][1]]);
					}
				}

				if (vertices.getCount())
				{
					Matrix4 mtx2 = viewProj * mtx;
					ri.debugDraw(PGeometry::PE_PRIMITIVE_LINES, vertices.getArray(), color, NULL, vertices.getCount(), &mtx2);
				}
			}
		}

		// Description:
		// Adds a callback to render the light.
		// Arguments:
		// light : The light to render.
		// camera : The camera.
		// size : The size to render the light.
		// renderer : The renderer with which to render the light.
		void RenderLight(const PRendering::PLight &light, const PCamera &camera, float size, PRendering::PRenderer &renderer)
		{
			void *userData = NULL;
			renderer.addRenderCallbackWithAllocatedBuffer(RenderLightCallback, sizeof(PLightRenderData), userData);
			if (userData)
				new(userData) PLightRenderData(light, camera, size);
		}

	} //! End of PSamplesCommon Namespace
} //! End of Phyre Namespace
