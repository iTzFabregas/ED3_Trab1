<h1>Estrutura de Dados III - Trabalho 1</h1>

<div align="justify" >
<p>Este trabalho teve como objetivo armazenar dados em um arquivo binário, bem
como desenvolver funcionalidades para a manipulação desses dados. Um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados. 
O tamanho da página de disco adotado foi de 960 <i>bytes</i>.</p>

<p>O programa oferece as seguintes funcionalidades:</p>

<li>1) Permitir a leitura de vários registros obtidos a partir de um arquivo de entrada no
formato csv e a gravação desses registros em um arquivo de dados de saída. 
O arquivo de dados de entrada não contém registros removidos.</br>

<strong>Entrada do programa para a funcionalidade:</br>
1 arquivoEntrada.csv arquivoSaida.bin</strong>
<hr>

<li>2) Permitir a recuperação dos dados de todos os registros armazenados em um arquivo
de dados de entrada, mostrando os dados de forma organizada na saída padrão para
permitir a distinção dos campos e registros. O tratamento de ‘lixo’ é feito de
forma a permitir a exibição apropriada dos dados. Registros marcados como
logicamente removidos não são exibidos.</br>

<strong>Entrada do programa para a funcionalidade:</br>
2 arquivoEntrada.csv</strong>
<hr>

<li>3) Permitir a recuperação dos dados de todos os registros de um arquivo de dados de
entrada, de forma que esses registros satisfaçam um critério de busca determinado pelo
usuário. Qualquer campo pode ser utilizado como forma de busca. Adicionalmente,
apenas um campo pode ser utilizado na busca. Essa funcionalidade pode ser executada N vezes.</br>

<strong>Entrada do programa para a funcionalidade:</br>
3 arquivoEntrada.csv N</br>
nomeCampo1 valorCampo1</br>
...</br>
nomeCampoN valorCampoN</strong>
<hr>

<li>4) Permitir a remoção lógica de registros em um arquivo de dados de entrada, baseado
na abordagem dinâmica de reaproveitamento de espaços de registros logicamente
removidos. A implementação dessa funcionalidade foi realizada usando o
conceito de lista de registros logicamente removidos. Como o arquivo possui registros de tamanho
fixo, a lista foi implementada como uma pilha. Os registros a serem removidos
são aqueles que satisfaçam um critério de busca determinado pelo usuário. Note que qualquer campo pode ser
utilizado como forma de remoção. Essa funcionalidade pode ser executada N vezes.</br>

<strong>Entrada do programa para a funcionalidade:</br>
4 arquivoEntrada.csv N</br>
nomeCampo1 valorCampo1</br>
...</br>
nomeCampoN valorCampoN</strong>
<hr>

<li>5) Permitir a inserção de novos registros em um arquivo de dados de entrada de um
determinado tipo, baseado na abordagem dinâmica de reaproveitamento de espaços de
registros logicamente removidos. A implementação dessa funcionalidade foi
realizada usando o conceito de lista de registros logicamente removidos. Como o arquivo possui registros
de tamanho fixo, a lista foi implementada como uma pilha. O lixo que permanece
no registro logicamente removido e que é reutilizado é identificado pelo
caractere ‘$’. Na entrada desta funcionalidade, os dados são referentes aos seguintes
campos, na seguinte ordem: idConecta, nomePoPs, nomePais, siglaPais,
idPoPsConectado, medidaVelocidade, velocidade. Campos com valores nulos, na
entrada da funcionalidade, são identificados com NULO. Os valores dos
campos do tipo string devem ser especificados entre aspas duplas (").Essa funcionalidade pode ser executada N vezes.</br>

<strong>Entrada do programa para a funcionalidade:</br>
5 arquivoEntrada.csv N</br>
idConecta1 nomePoPs1 nomePais1 siglaPais1 idPoPsConectado1 medidaVelocidade1 velocidade1</br>
...</br>
idConectaN nomePoPsN nomePaisN siglaPaisN idPoPsConectadoN medidaVelocidadeN velocidadeN</strong>
<hr>

<li>6) Permitir a compactação eficiente (desfragmentação) do arquivo de dados. A
compactação elimina os registros removidos, deixando no arquivo de dados somente
os registros marcados como não removidos. A compactação não elimina o lixo,
ou seja, não elimina o caractere ‘$’. Como entrada dessa funcionalidade, tem-se
um arquivo de dados binário que pode conter (ou não) registros logicamente
removidos.</br>

<strong>Entrada do programa para a funcionalidade:</br>
6 arquivoEntrada.csv</strong>
<hr>

<p>Para compilar os códigos, use o comando <code>make all</code></p>
<p>Para executar o programa, use o comando <code>make run</code></p>
<p>Para testar o programa, pode-se usar os arquivos da pasta <strong>tests</strong>, lembrando que alguns arquivos podem ser alterados</p>
