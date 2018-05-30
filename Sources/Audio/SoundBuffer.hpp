#pragma once

#include <string>
#include <vector>
#include "Audio/Audio.hpp"
#include "Resources/Resources.hpp"
#include "Maths/Vector3.hpp"

namespace fl
{
	/// <summary>
	/// Class that represents a sound buffer.
	/// </summary>
	class FL_EXPORT SoundBuffer :
		public IResource
	{
	private:
		std::string m_filename;
		unsigned int m_buffer;
	public:
		static std::shared_ptr<SoundBuffer> Resource(const std::string &filename)
		{
			auto resource = Resources::Get()->Get(filename);

			if (resource != nullptr)
			{
				return std::dynamic_pointer_cast<SoundBuffer>(resource);
			}

			auto result = std::make_shared<SoundBuffer>(filename);
			Resources::Get()->Add(std::dynamic_pointer_cast<IResource>(result));
			return result;
		}

		SoundBuffer(const std::string &filename);

		~SoundBuffer();

		std::string GetFilename() override { return m_filename; };

		FL_HIDDEN unsigned int GetBuffer() const { return m_buffer; };

		FL_HIDDEN static unsigned int LoadBufferWav(const std::string &filename);

		FL_HIDDEN static unsigned int LoadBufferOgg(const std::string &filename);
	};
}
