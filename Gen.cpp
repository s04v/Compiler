#include <Gen.h>
#include <string>


Gen::Gen() {
	f.open("out.asm", std::ofstream::out);
	//reg = 0;
	st.init_scope();
	ret = "";
	use_reg = 0;
	prev_reg = 0;

}

Gen::~Gen() {}

void Gen::start(std::vector<Node*> p) {

	for (int i = 0; i < p.size(); i++) {
		gen_var(p[i]);
	}

	std::cout << ret;
	f.close();
}

void Gen::release_reg() {
	if (use_reg > 0) {
		prev_reg = use_reg;
		use_reg--;
	}
}

void Gen::new_reg() {
	prev_reg = use_reg;
	use_reg++;

	//get_reg();

}

int Gen::alloc_register() {
	for (int i = 0; i < 4; i++) {
		if (freereg[i]) {
			freereg[i] = 0;
			return (i);
		}
	}
	return -1;
}

void Gen::free_register(int r) {
	if (freereg[r] != 0)
		m_assert(0, "Error trying to free register");

	freereg[r] = 1;
}

std::string Gen::get_reg(int r) {
	switch (r) {
	case 0:
		return "eax";
	case 1:
		return "ebx";
	case 2:
		return "ecx";
	case 3:
		return "edx";
	}

	return NULL;
}

int Gen::gen_expr(Node* node) {
	

	std::string result_reg;
	Node* left = node->left;
	Node* right = node->right;


	switch (node->type) {
	case ID_NAME: {
		return load_var(node->val);
	}
	case NUMBER_CONST:
	case FLOAT_CONST: {
		return load_const(node->val);
		break;
	}

	case N_SUB:
	case N_ADD: {
		int r1;
		int r2;

		if (right->type == N_MUL || right->type == N_DIV) {
			if (right->type == NUMBER_CONST)
				r1 = load_const(right->val);
			else
				r1 = gen_expr(right);

			if (left->type == NUMBER_CONST)
				r2 = load_const(left->val);
			else
				r2 = gen_expr(left);
		}
		else {

			if (left->type == NUMBER_CONST)
				r1 = load_const(left->val);
			else
				r1 = gen_expr(left);

			if (right->type == NUMBER_CONST)
				r2 = load_const(right->val);
			else
				r2 = gen_expr(right);

		}
		

		
		
		
		
		if(node->type == N_ADD)
			gen_add(r1, r2);
		else
			gen_sub(r1, r2);


		return r1;		
	}
	case N_MUL:
	case N_DIV:
		int r1;
		int r2;

		if (right->type == N_ADD || right->type == N_SUB) {
			
			if (right->type == NUMBER_CONST)
				r1 = load_const(right->val);
			else
				r1 = gen_expr(right);

			if (left->type == NUMBER_CONST)
				r2 = load_const(left->val);
			else
				r2 = gen_expr(left);

			
		}
		else {
			if (left->type == NUMBER_CONST)
				r1 = load_const(left->val);
			else
				r1 = gen_expr(left);

			if (right->type == NUMBER_CONST)
				r2 = load_const(right->val);
			else
				r2 = gen_expr(right);

			
		}

			if (node->type == N_MUL)
				gen_mul(r1, r2);
			else
				gen_div(r1, r2);

		return r1;
	
	default:
		break;
	}
	
	
	return -2; 
}

void Gen::gen_var(Node* node) {
	switch (node->type) {
	case VAR_DEF: {
		// add var to symtable 
		st.add(VAR_SYM, node->val);
		
		int r =  gen_expr(node->left);

		save_var(node->val, r);

		//return r;
		break;
	}
	}
}


int Gen::load_const(std::string v) {
	int r = alloc_register();
	ret += "mov " + get_reg(r) + ", " + v + "\n";

	return r;
}

int Gen::load_var(std::string n) {
	int r = alloc_register();
	Symbol v = st.get(n);
	ret += "mov " + get_reg(r) + ", DWORD PTR [rbp -" + std::to_string((v.index + 1) * 4) + "]\n";

	return r;
}
int Gen::save_var(std::string n, int r) {

	Symbol v = st.get(n);
	ret += "mov DWORD PTR [rbp - " + std::to_string((v.index + 1)  * 4) + "], " + get_reg(r) + "\n";

	free_register(r);
	//TODO: delete
	return -1;
}



int Gen::gen_add(int r1, int r2) {
	ret += "add " + get_reg(r1) + ", " + get_reg(r2) + "\n";

	free_register(r2);
	return r1;
}

int Gen::gen_mul(int r1, int r2) {
	ret += "mul " + get_reg(r1) + ", " + get_reg(r2) + "\n";

	free_register(r2);
	return r1;
}

int Gen::gen_sub(int r1, int r2) {
	ret += "sub " + get_reg(r1) + ", " + get_reg(r2) + "\n";

	free_register(r2);
	return r1;
}
int Gen::gen_div(int r1, int r2) {
	ret += "div " + get_reg(r1) + ", " + get_reg(r2) + "\n";

	free_register(r2);
	return r1;
}
