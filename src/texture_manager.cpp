#include "inc/texture_manager.hpp"
#include <sstream>
#include <tinyxml2.h>
#include <inc/utility.hpp>

namespace astroblaster {
	bool TextureManager::add_texture(std::string filename, unsigned int mode) {
		if (!this->textures.count(filename)) {
			if (mode & static_cast<unsigned int>(TextureModes::Sheet)) {
				tinyxml2::XMLDocument sheet;
				sheet.LoadFile(this->get_full_resource_path(filename).c_str());
				if (sheet.ErrorID()) {
					return false;
				}
				this->textures[filename] = std::make_unique<sf::Texture>();
				if (!this->textures.at(filename)->loadFromFile(this->get_full_resource_path(sheet.RootElement()->Attribute("imagePath")))) {
					this->textures.erase(this->textures.find(filename));
					return false;
				}
				const sf::Texture *atlas = this->textures.at(filename).get();
				tinyxml2::XMLElement *subtexture = sheet.RootElement()->FirstChildElement("SubTexture");
				while (subtexture) {
					this->subtextures.emplace(subtexture->Attribute("name"), std::pair(atlas, sf::Rect(subtexture->IntAttribute("x"), subtexture->IntAttribute("y"), subtexture->IntAttribute("width"), subtexture->IntAttribute("height"))));
					subtexture = subtexture->NextSiblingElement("SubTexture");
				}
			}
			else {
				this->textures[filename] = std::make_unique<sf::Texture>();
				if (!this->textures.at(filename)->loadFromFile(this->get_full_resource_path(filename))) {
					this->textures.erase(this->textures.find(filename));
					return false;
				}
			}
			if (mode & static_cast<unsigned int>(TextureModes::Repeat)) {
				this->textures.at(filename)->setRepeated(true);
			}
		}
		return true;
	}

	const sf::Texture* TextureManager::get_texture(std::string name) const {
		try {
			return this->textures.at(name).get();
		}
		catch (std::out_of_range) {
			// we'll prefer default return below
		}
		return nullptr;
	}

	std::pair<const sf::Texture*, sf::Rect<int>> TextureManager::get_subtexture(std::string name) const {
		try {
			return this->subtextures.at(name);
		}
		catch (std::out_of_range) {
			// we'll prefer default return below
		}
		return std::pair(nullptr, sf::Rect<int>(0, 0, 0, 0));
	}

	std::string TextureManager::get_full_resource_path(std::string_view filename) const {
		std::stringstream ss;
		ss << "res/img/" << filename;
		return ss.str();
	}
}