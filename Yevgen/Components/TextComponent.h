#pragma once
#include <string>
#include "RenderComponent.h"
#include "Font.h"


namespace yev{
	class TextComponent final : public RenderComponent
	{
	public:
		void Update() override;
		

		void SetText(const std::string& text);

		TextComponent(GameObject* owner, const std::string& text, const std::shared_ptr<yev::Font>& font);
		TextComponent(GameObject* owner, const std::shared_ptr<yev::Font>& font);
		~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<yev::Font> m_font;
	};


}

