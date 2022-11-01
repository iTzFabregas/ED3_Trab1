//recebe os inputs do teclado e guarda qual sera o campo usado na busca
int receive_inputs(char fieldname[][20], char field[][20], int type_field[], int num_searches);

//executa o comando 3, busca registros que tenham um campo igual ao especificado pelo teclado
void command3(char* filename, int num_searches);