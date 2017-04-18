[SIE CONFIDENTIAL DOCUMENT]
PhyreEngine(TM) Package 3.17.0.0
Copyright (C) 2016 Sony Interactive Entertainment Inc.
All Rights Reserved.

Text Sample

Introduction
This sample demonstrates how to render text.

Please see the User Guide for more information.

On Windows:
Y - Toggle sample gui.

On PlayStation(R)3, PlayStation(R)Vita and PlayStation(R)4:
Start/Options - Toggle sample gui.

Use mouse, controller or touchscreen to control camera movement.

Usage
Text

Categories
Text

Changes
14/09/2010 0.1  Original version
19/09/2011 0.2  Updated to clamp camera distance between 0 and 500
                units.
24/02/2012 0.3  Removed the declaration of the PWorld object. This is
                now declared in the Framework.
23/04/2012 0.4  Added a setBufferCount() call for dynamic text.
25/06/2012 0.6  Updated to use PUtilityText::CreateText() API.
30/07/2012 0.7  Updated to strip directory name from asset path
                string.
22/05/2014 0.8  Added support for Microsoft Visual Studio 2013.
05/09/2014 0.9  Removed support for Microsoft Visual Studio 2010.
17/12/2014 0.10 Updated project file to use SCE_PHYRE environment
                variable to simplify changing or copying to a new
                location.
25/02/2015 0.11 Added sample gui.
03/12/2015 0.12 Added support for Microsoft Visual Studio 2015.
21/07/2016 0.13 Moved thirdpersongametemplate animate() into
                PFrameworkApplication defaultAnimate().