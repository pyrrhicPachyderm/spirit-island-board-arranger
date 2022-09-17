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

class SVG {
	protected:
		SVGElement element;
	public:
		
		void setViewbox(double x, double y, double width, double height) {
			std::string dimensionString = std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height);
			element.setAttribute("viewBox", dimensionString);
		}
		
		void setDisplayDimensions(std::string width, std::string height) {
			element.setAttribute("width", width);
			element.setAttribute("height", height);
		}
		
		SVG():
			element(SVGElement("svg")) {};
		SVG(double width, double height, std::string displayWidth, std::string displayHeight):
			SVG()
		{
			setViewbox(0, 0, width, height);
			setDisplayDimensions(displayWidth, displayHeight);
		};
		SVG(double x, double y, double width, double height, std::string displayWidth, std::string displayHeight):
			SVG()
		{
			setViewbox(x, y, width, height);
			setDisplayDimensions(displayWidth, displayHeight);
		};
		
		void addElement(SVGElement child) {
			element.addChild(child);
		}
		
		std::string asString() const {
			std::string result = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			result += element.asString(0);
			return result;
		}
};

#endif
