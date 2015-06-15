struct Node {

	int data;
	struct Node* left;
	struct Node* right;


};


__kernel void Find (__global void* node, __global int* out, int* key_list) {

	int gid = get_global_id(0);

	if (!node) {
		// error
		return;
	}
	struct Node* tmp = (struct Node*)(node);


	while (tmp != NULL) {

		if (key_list[gid] > tmp->data) {

			tmp = tmp->right;

		} else if (key_list[gid] < tmp->data){

			tmp = tmp->left;
		} else {
			
			out[gid]=1;
			break;
		}


	}



	


}















