#pragma once
#include <string>
#include "RenderComponent.h"
#include "Font.h"

class TextComponent final : public RenderComponent
{
public:
	void Update() override;
	//void Render() const override;

	void SetText(const std::string& text);

	TextComponent(std::weak_ptr<dae::GameObject> owner, const std::string& text, std::shared_ptr<dae::Font> font );
	TextComponent(std::weak_ptr<dae::GameObject> owner, std::shared_ptr<dae::Font> font);
	~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;
private:
	bool m_needsUpdate;
	std::string m_text;
	std::shared_ptr<dae::Font> m_font;
};

