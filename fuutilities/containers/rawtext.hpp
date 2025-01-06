#pragma once

#include <string>

namespace Utils
{
	class RawText
	{
	private:
		std::string raw;
		int			length = 0;
		//which character is the cursor pointing at?
		int			cursor = 0;

	public:
		RawText() = default;

		/**
		 * Create a raw text from a std::string.
		 *
		 * @param str
		 */
		RawText(const std::string& str);

		/**
		 * Move the cursor.
		 *
		 * @param pos
		 */
		void setCursor(const int pos);

		/**
		 * Get the line where the cursor is, then move the cursor to the beginning of the next line.
		 *
		 * @param out
		 * @return
		 */
		bool getline(std::string& out);

		/**
		 * Get the entire text.
		 *
		 * @return
		 */
		std::string& getRawText();
	};
}