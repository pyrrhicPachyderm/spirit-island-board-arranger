#ifndef SVG_HPP
#define SVG_HPP

#include <vector>
#include <map>
#include <string>

class SVGElement {
	public:
		const std::string name;
	protected:
		std::map<std::string, std::string> attributes;
		std::vector<SVGElement> children;
	public:
		SVGElement(std::string name):
			name(name) {};
		
		void setAttribute(std::string name, std::string value) {
			attributes[name] = value;
		}
		
		void addChild(SVGElement child) {
			children.push_back(child);
		}
	protected:
		static const std::string INDENT_STRING;
		
		static std::string indentString(size_t level) {
			std::string result = "";
			for(size_t i = 0; i < level; i++) result += INDENT_STRING;
			return result;
		}
	public:
		std::string asString(size_t indent) const {
			std::string result = indentString(indent) + "<" + name;
			for(const auto &attribute : attributes) {
				result += " " + attribute.first + "=\"" + attribute.second + "\"";
			}
			if(children.size() == 0) {
				result += "/>\n";
			} else {
				result += ">\n";
				for(const SVGElement &child : children) {
					result += child.asString(indent + 1);
				}
				result += indentString(indent) + "</" + name + ">\n";
			}
			return result;
		}
};

const std::string SVGElement::INDENT_STRING = "\t";

#endif
