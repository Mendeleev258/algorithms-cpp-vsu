#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace ttree
{
	struct NODE
	{
		NODE* ptrs[26];
		bool eow = false;
		NODE()
		{
			for (short j = 0; j < 26; j++)
				ptrs[j] = nullptr;
		};
	};

	using ptrNODE = NODE*;

	struct TTREE
	{
	private:
		ptrNODE root;

	public:
		TTREE() { root = nullptr; }
		TTREE(const char* file_name);
		bool empty();
		bool all_prts_empty(ptrNODE t);
		ptrNODE get_root()
		{
			return root;
		}
		void set_root(ptrNODE t)
		{
			root = t;
		}
		~TTREE();
		void print(bool words, std::ostream& stream = std::cout);
	};
	// -------------------------------------
	void printW(ttree::ptrNODE t, std::string word);
}