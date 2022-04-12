#pragma once

namespace PH {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:time_(time)
		{
		}
		operator float() const { return time_; } // 隐式转换为float时自动返回time_

		float GetSeconds()const { return time_; }
		float GetMilliseconds()const { return time_ * 1000.0f; }
	private:
		float time_;
	};

}