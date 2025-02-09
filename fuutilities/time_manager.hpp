#pragma once

#include <cstdint>
#include <chrono>
#include <cassert>

namespace Time
{
	template <int NType>
	class TimeOrigin
	{
	};

	// compute time since epoch
	using Epoch = TimeOrigin<0>;
	// compute time since application start
	using App = TimeOrigin<1>;

	// TODO : template for time type (milli, seconds, minutes, ...)
	class TimeManager
	{
	private:
		/**
		 * @brief Application start time
		 *
		 */
		double m_startTime = -1.f;

		/**
		 * @brief Time at a certain frame (set with the markFrame function)
		 *
		 */
		double m_frameMark = -1.f;

		/**
		 * @brief Time between two frame marks
		 *
		 */
		double m_deltaTime = -1.f;

		template <typename TTimeOrigin, typename TType>
		inline TType since()
		{
			static_assert(sizeof(T) == -1, "Time origin and return type specification required");
			return nullptr;
		}

	public:
		TimeManager()
		{
			m_startTime = since<Epoch, double>();
			m_frameMark = m_startTime;
			markFrame();
		}

		template <>
		inline double since<Epoch, double>()
		{
			const std::chrono::duration<double> now = std::chrono::steady_clock::now().time_since_epoch();
			return now.count();
		}

		template <>
		inline uint64_t since<Epoch, uint64_t>()
		{
			time(NULL);
		}

		template <>
		inline double since<App, double>()

		{
			assert(m_startTime != -1.f);
			return since<Epoch, double>() - m_startTime;
		}

		/**
		 * Mark a frame with a time stamp (used for delta time)
		 */
		void markFrame()
		{
			double t = since<Epoch, double>();
			m_deltaTime = t - m_frameMark;
			m_frameMark = t;
		}

		/**
		 * Get delta time
		 */
		inline double deltaTime() const { return m_deltaTime; }

		/**
		 * Get frame rate
		 */
		inline double getFrameRate() { return 1.f / m_deltaTime; }
	};

	// TODO : template for time type (milli, seconds, minutes, ...)
	static class Measure
	{
		/**
		 * @brief Start measuring elapsed time
		 *
		 * @return std::chrono::steady_clock::time_point
		 */
		static inline std::chrono::steady_clock::time_point start()
		{
			return std::chrono::steady_clock::now();
		}

		/**
		 * @brief Stop measuring elapsed time (milliseconds)
		 *
		 * @param start
		 * @return int64_t
		 */
		static inline int64_t end(std::chrono::steady_clock::time_point start)
		{
			const auto end = std::chrono::steady_clock::now();

			return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
		}
	};
}
