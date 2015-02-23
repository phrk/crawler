#include "page.h"

namespace crw {

	bool isImageLink(const std::string &_url)
	{
		if (_url.find(".jpg") == -1 &&
				_url.find(".jpeg") == -1 &&
				_url.find(".pdf") == -1 &&
				_url.find(".png") == -1 &&
				_url.find(".gif") == -1 &&
				_url.find(".mp4") == -1 &&
				_url.find(".avi") == -1 &&
				_url.find(".doc") == -1 &&
				_url.find(".docx") == -1 &&
				_url.find(".pdf") == -1 &&
				_url.find(".ppt") == -1 &&
				_url.find(".rar") == -1 &&
				_url.find(".zip") == -1 &&
				_url.find(".7z") == -1 &&
				_url.find(".cdr") == -1 &&
				_url.find(".xml") == -1)
		{
			return false;
		}
		return true;
	}

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
			(href = gumbo_get_attribute(&node->v.element.attributes, "href"))) 
			if (!isImageLink(href->value)) {
				
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
	void leaveOnlyWords (std::string &_s) {
		
		fix_utf8_string(_s);
		toLowerUtf8(_s);
		
		std::vector<std::string> words;
		std::set<uint32_t> delims;
		delims.insert(0x2E); // '.'
		delims.insert(0xA); // '\n' 
		
		delims.insert(0x20); // ' '
		delims.insert(0x2C); // ','
		delims.insert(0x3B); // ';'
		delims.insert(0x3A); // ':'
		delims.insert(0x2D); // '-'
		delims.insert(0x28); // '('
		delims.insert(0x29); // ')'
		delims.insert(0x7B); // '{'
		delims.insert(0x7D); // '}'
		delims.insert(0x22); // '"'
		delims.insert(0x27); // '''
		delims.insert(0x3C); // '<'
		delims.insert(0x3E); // '>'
		
		splitUtf8(_s, delims, words);
		
		_s = "";
		
		for (int i = 0; i<words.size(); i++) {
	
			eraseNonCharsUtf8(words[i]);
			_s.append(words[i]);
			_s.append(" ");
		}					
						
	}
	
	Page::Page(const Link &_link, const std::string &_html):
	link(_link) {
		
		content.html = _html;
		
		GumboOutput* output = gumbo_parse(content.html.c_str());
		content.text = cleantext(output->root);
		
		leaveOnlyWords(content.text);
		
		findLinks(output->root);
		gumbo_destroy_output(&kGumboDefaultOptions, output);
	}

}
