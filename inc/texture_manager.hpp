#pragma once
#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <unordered_map>
#include <utility>
#include <string_view>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace astroblaster {
	class TextureManager {
		public:
			bool add_texture(std::string filename, unsigned int mode = 0u);
			const sf::Texture* get_texture(std::string name) const;
			std::pair<const sf::Texture*, sf::Rect<int>> get_subtexture(std::string name) const;
		private:
			std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
			std::unordered_map<std::string, std::pair<const sf::Texture*, sf::Rect<int>>> subtextures;
			std::string get_full_resource_path(std::string_view s) const;
	};
}

#endif