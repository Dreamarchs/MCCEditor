#include "include/ApiDef.h"
#include "EditorVKContext.h"

#define STD_OSTREAM 1
#define STD_ERR 2



static std::string ShaderSourceLocation = "";


int InitializeRendererFromWindow(HWND targetWnd, RECT rect)
{
	vkCtx = std::shared_ptr<EditorVKContext>(new EditorVKContext(targetWnd, rect));

#ifndef NDEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE* STANDARD_OUT, *STANDARD_ERROR;
	freopen_s(&STANDARD_OUT, "CONOUT$", "w", stdout);
	freopen_s(&STANDARD_ERROR, "CONOUT$", "w", stderr);
#endif

	try
	{
		std::cout << "Initializing Vulkan Renderer" << std::endl;
		vkCtx->InitializeVulkan();
		vkCtx->InitializeSwapchain();
		vkCtx->InitializeGraphicsPipeline(ShaderSourceLocation);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void Shutdown()
{
	vkCtx.reset();
}

SCENEVIEW_API void SetShaderLocation(const std::string& shaderLocation)
{
	ShaderSourceLocation = shaderLocation;
}
