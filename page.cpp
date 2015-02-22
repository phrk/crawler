#include "page.h"

namespace crw {

	static std::string cleantext(GumboNode* node) {
		if (node->type == GUMBO_NODE_TEXT) {
		return std::string(node->v.text.text);
		} else if (node->type == GUMBO_NODE_ELEMENT &&
		node->v.element.tag != GUMBO_TAG_SCRIPT &&
		node->v.element.tag != GUMBO_TAG_STYLE) {
		std::string contents = "";
		GumboVector* children = &node->v.element.children;
		for (unsigned int i = 0; i < children->length; ++i) {
		const std::string text = cleantext((GumboNode*) children->data[i]);
		if (i != 0 && !text.empty()) {
		contents.append(" ");
		}
		contents.append(text);
		}
		return contents;
		} else {
		return "";
		}
	}

	void Page::findLinks(GumboNode* node) {
		
		if (node->type != GUMBO_NODE_ELEMENT) {
			return;
		}
		GumboAttribute* href;
		if (node->v.element.tag == GUMBO_TAG_A &&
			(href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
				
				try {
					
					Link newlink ( href->value );
					
					if (newlink.domain == link.domain)
						outbound_links_in.push_back(newlink);
					else
						outbound_links_out.push_back(newlink);	
					
				} catch (...) {
					
					//std::cout << "Page::findLinks exception: " << href->value << std::endl;
				}
		}
			GumboVector* children = &node->v.element.children;
			for (unsigned int i = 0; i < children->length; ++i) {
				findLinks(static_cast<GumboNode*>(children->data[i]));
		}
	}

/*	Page::Page(const Link &_link):
		link(_link)
		 {
	}*/
	
	Page::Page(const Link &_link, const std::string &_html):
	link(_link) {
		
		content.html = _html;
		
		GumboOutput* output = gumbo_parse(content.html.c_str());
		content.text = cleantext(output->root);
		
		findLinks(output->root);
		gumbo_destroy_output(&kGumboDefaultOptions, output);
	}

}
