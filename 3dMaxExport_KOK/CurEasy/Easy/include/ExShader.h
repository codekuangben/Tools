#ifndef _EXSHADER_H
#define _EXSHADER_H

#include "ExPrerequisites.h"
#include "paramList.h"

namespace EasyOgreExporter
{
	class ExMaterial;

	class ExShader
	{
	public:
		enum ShaderType
		{
			ST_NONE,
			// ambient vertex shader
			ST_VSAM,
			// ambient pixel shader
			ST_FPAM,
			// lighting vertex shader
			ST_VSLIGHT,
			// lighting pixel shader
			ST_FPLIGHT,
			// lighting vertex shader multipass
			ST_VSLIGHT_MULTI,
			// lighting pixel shader multipass
			ST_FPLIGHT_MULTI
		};

		enum ShaderPass
		{
			SP_NONE,
			// ambient pass
			SP_AMBIENT,
			// lighting pass
			SP_LIGHT,
			// lighting multi pass
			SP_LIGHT_MULTI,
			// decal pass
			SP_DECAL,
			// non supported
			SP_NOSUPPORT
		};
	protected:
		bool bRef;
		bool bNormal;
		bool bAmbient;
		bool bDiffuse;
		bool bSpecular;
		ShaderType m_type;

		std::string m_name;
		std::string m_content;
		std::string m_program;
		std::string m_params;

	public:
		ExShader(std::string name);
		~ExShader();

		virtual void constructShader(ExMaterial* mat);
		std::string& getName();
		std::string& getContent();
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};

	class ExVsAmbShader : public ExShader
	{
	public:
		ExVsAmbShader(std::string name);
		~ExVsAmbShader();

		virtual void constructShader(ExMaterial* mat);
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};

	class ExFpAmbShader : public ExShader
	{
	public:
		ExFpAmbShader(std::string name);
		~ExFpAmbShader();

		virtual void constructShader(ExMaterial* mat);
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};

	class ExVsLightShader : public ExShader
	{
	public:
		ExVsLightShader(std::string name);
		virtual ~ExVsLightShader();

		virtual void constructShader(ExMaterial* mat);
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};

	class ExFpLightShader : public ExShader
	{
	public:
		ExFpLightShader(std::string name);
		~ExFpLightShader();

		virtual void constructShader(ExMaterial* mat);
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};

	class ExVsLightShaderMulti : public ExShader
	{
	public:
		ExVsLightShaderMulti(std::string name);
		virtual ~ExVsLightShaderMulti();

		virtual void constructShader(ExMaterial* mat);
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};

	class ExFpLightShaderMulti : public ExShader
	{
	public:
		ExFpLightShaderMulti(std::string name);
		~ExFpLightShaderMulti();

		virtual void constructShader(ExMaterial* mat);
		virtual std::string& getUniformParams(ExMaterial* mat);
		virtual std::string& getProgram(std::string baseName);
	};
};

#endif