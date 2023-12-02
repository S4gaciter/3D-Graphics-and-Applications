#include "CommandDictionary.h"

#include "CmdDrawPixel.h"
#include "CmdSetColor.h"
#include "CmdSetResolution.h"
#include "CmdSetFillMode.h"
#include "CmdVarFloat.h"
#include "CmdBeginDraw.h"
#include "CmdAddVertex.h"
#include "CmdEndDraw.h"
#include "CmdSetViewport.h"
#include "CmdShowViewport.h"
#include "CmdSetClipping.h"
#include "CmdPushTranslation.h"
#include "CmdPushScaling.h"
#include "CmdPopMatrix.h"
#include "CmdPushRotationX.h"
#include "CmdPushRotationY.h"
#include "CmdPushRotationZ.h"
#include "CmdSetCameraDirection.h"
#include "CmdSetCameraPosition.h"
#include "CmdSetCameraNear.h"
#include "CmdSetCameraFar.h"
#include "CmdSetCameraFov.h"
#include "CmdSetCullMode.h"
#include "CmdEnableDepth.h"
#include "CmdLights.h"
#include "CmdMaterial.h"
#include "CmdModel.h"
#include "CmdSetShading.h"

CommandDictionary* CommandDictionary::Get()
{
	static CommandDictionary sInstance;
	return &sInstance;
}

CommandDictionary::CommandDictionary()
{
	// Initialize dictionary

	// Setting commands
	RegisterCommand<CmdSetResolution>();
	RegisterCommand<CmdSetColor>();
	RegisterCommand<CmdSetFillMode>();
	RegisterCommand<CmdSetViewport>();
	RegisterCommand<CmdShowViewport>();
	RegisterCommand<CmdSetClipping>();
	RegisterCommand<CmdSetCullMode>();
	RegisterCommand<CmdEnableDepth>();

	// Variable commands
	RegisterCommand<CmdVarFloat>();
	RegisterCommand<CmdPushTranslation>();
	RegisterCommand<CmdPushScaling>();
	RegisterCommand<CmdPushRotationX>();
	RegisterCommand<CmdPushRotationY>();
	RegisterCommand<CmdPushRotationZ>();
	RegisterCommand<CmdPopMatrix>();

	// Camera Commands
	RegisterCommand<CmdSetCameraDirection>();
	RegisterCommand<CmdSetCameraPosition>();
	RegisterCommand<CmdSetCameraNear>();
	RegisterCommand<CmdSetCameraFar>();
	RegisterCommand<CmdSetCameraFov>();

	// Light Commands
	RegisterCommand<CmdSetLightAmbient>();
	RegisterCommand<CmdSetLightDiffuse>();
	RegisterCommand<CmdSetLightSpecular>();
	RegisterCommand<CmdAddDirectionalLight>();
	RegisterCommand<CmdAddPointLight>();
	RegisterCommand<CmdAddSpotLight>();
	RegisterCommand<CmdSetShading>();

	// Material Commands
	RegisterCommand<CmdSetMaterialAmbient>();
	RegisterCommand<CmdSetMaterialDiffuse>();
	RegisterCommand<CmdSetMaterialSpecular>();
	RegisterCommand<CmdSetMaterialShininess>();

	// Rasterization commands
	RegisterCommand<CmdDrawPixel>();
	RegisterCommand<CmdBeginDraw>();
	RegisterCommand<CmdAddVertex>();
	RegisterCommand<CmdEndDraw>();
	RegisterCommand<CmdModel>();
}

TextEditor::LanguageDefinition CommandDictionary::GenerateLanguageDefinition()
{
	TextEditor::LanguageDefinition langDef;

	langDef.mName = "Pix";

	langDef.mKeywords.insert("var");

	for (auto& [keyword, command] : mCommandMap)
	{
		TextEditor::Identifier id;
		id.mDeclaration = command->GetDescription();
		langDef.mIdentifiers.insert(std::make_pair(keyword, id));
	}

	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\$[a-zA-Z_]+", TextEditor::PaletteIndex::Keyword));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\'\\\\?[^\\']\\'", TextEditor::PaletteIndex::CharLiteral));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", TextEditor::PaletteIndex::Punctuation));

	langDef.mCommentStart = "/*";
	langDef.mCommentEnd = "*/";
	langDef.mSingleLineComment = "//";

	langDef.mAutoIndentation = true;
	langDef.mCaseSensitive = true;

	return langDef;
}

Command* CommandDictionary::CommandLookup(const std::string& keyword)
{
	auto iter = mCommandMap.find(keyword);
	if (iter == mCommandMap.end())
		return nullptr;
	return iter->second.get();
}

template <class T>
void CommandDictionary::RegisterCommand()
{
	static_assert(std::is_base_of_v<Command, T>, "Invalid command type.");
	auto newCommand = std::make_unique<T>();
	mCommandMap.emplace(newCommand->GetName(), std::move(newCommand));
}