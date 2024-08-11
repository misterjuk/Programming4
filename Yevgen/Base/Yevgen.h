#pragma once
#include <string>
#include <functional>

namespace yev
{
	class Yevgen
	{
	public:
		explicit Yevgen(const std::string& dataPath);
		~Yevgen();
		void Run(const std::function<void()>& load);

		void FixedUpdate();
		void Update();
		void Render();

		Yevgen(const Yevgen& other) = delete;
		Yevgen(Yevgen&& other) = delete;
		Yevgen& operator=(const Yevgen& other) = delete;
		Yevgen& operator=(Yevgen&& other) = delete;

	private:

		const float FIXED_TIME_STEP = 0.15f;
	};
}