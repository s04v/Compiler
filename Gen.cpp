#include <Gen.h>
#include <string>


Gen::Gen() {
	f.open("out.asm", std::ofstream::out);
	reg = 0;
	use_reg = "eax";
	prev_reg = "eax";

}

Gen::~Gen() {}

void Gen::start(Node* node) {
	gen_var(node);
	
	f.close();
}

std::string Gen::gen_expr(Node* node) {
	

	std::string ret = "";

	Node* left = node->left;
	Node* right = node->right;


	switch (node->type) {
	case NUMBER_CONST:
	case FLOAT_CONST: {

		ret = "mov " + use_reg + ", " + node->val + "\n";
		break;
	}
	case N_ADD: {
		ret += gen_expr(left);

		new_reg();
		ret += gen_expr(right);
		ret += "add "+ use_reg +", "+ prev_reg +"\n";

	}
	default:
		break;
	}
	prev_reg = use_reg;
	release_reg();
	return ret;
}

void Gen::gen_var(Node* node) {
	switch (node->type) {
	case VAR_DEF: {
		// add var to symtable 
		std::string e = gen_expr(node->left);
		
		f << e;
		//f << "mov DWORD PTR [rbp-4], " + e;
		break;
	}
	}
}


void Gen::release_reg() {
	if(reg > 0){
		reg--;
		get_reg();
	}
}

void Gen::get_reg() {
	
	switch (reg) {
	case 0:
		use_reg = "eax";
		break;
	case 1:
		use_reg = "ebx";
		break;
	case 2:
		use_reg = "ecx";
		break;
	case 3:
		use_reg = "edx";
		break;
	}

}
void Gen::new_reg() {
	
	reg++;
	get_reg();
	
}
