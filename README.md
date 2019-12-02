# ProjetoComputacaoGrafica
Projeto de Computação Gráfica

O objetivo deste projeto é realizar adaptações e melhorias em uma aplicação web baseada em Computação Gráfica. A aplicação educacional permite criar apresentações multimídia para estudo de objetos 3D. A aplicação é composta por duas páginas web:

Página de associação de dados
Página de apresentação multimídia

A página de associação de dados permite criar uma apresentação multimídia por meio da associação de dados como texto descritivo, imagens e vídeo aos objetos. Também, é possível associar dados a regiões de interesse do objeto usando uma ferramenta de seleção 2D. Uma apresentação multimídia é representada por um arquivo xml, o qual contém as associações dos dados. A página de apresentação multimídia, por sua vez, possibilita a visualização do modelo 3D e dos dados associados. Ela é criada a partir do arquivo xml da apresentação.

A aplicação web requer um servidor web e acesso a um banco de dados para o seu funcionamento. Para possibilitar o desenvolvimento e execução offline é necessária a seguinte alteração.

Atualmente, o arquivo xml gerado e os dados associados são enviados para armazenamento do servidor. Por esse motivo, é necessário que os dados e o arquivo xml seja salvo localmente. Assim, deve existir um diretório no computador local para cada apresentação criada, contendo os dados da associação e o arquivo xml. (Alexsander e Adam)

Usando a versão local, as equipes deverão implementar alterações e melhorias, sugeridas abaixo:

Atualmente, o modelo 3D é carregado automaticamente  na página de associação de dados a partir do diretório local da aplicação. Deseja-se que seja criada uma nova página web inicial, que permita ao usuário selecionar um arquivo de modelo 3D disponível no computador local. Após a seleção do arquivo, deverá ser exibida a página de associação de dados. Ao final, o  modelo 3D carregado deverá ser salvo e armazenado no diretório da apresentação multimídia, junto aos dados associados e ao arquivo xml. (Franciedson e Vinícius)
A página de associação de dados deverá possibilitar o carregamento de arquivos de modelos 3D no formato PLY (binário e ASCII), tal como exportado pelo Meshlab. Informações sobre o formato PLY em:
https://en.wikipedia.org/wiki/PLY_(file_format)
http://paulbourke.net/dataformats/ply/
Exemplos de arquivos de modelos 3D nesse formato:
http://graphics.stanford.edu/data/3Dscanrep/(Ramon e Francisco)
Aprimoramento da ferramenta de seleção 2D. Atualmente, essa ferramenta permite selecionar uma região retangular do objeto 3D. Deseja-se então incluir uma ferramenta de associação circular, que permita seleciona uma região circular do objeto. Para isso, o algoritmo de seleção 2D deverá ser estudado e adaptado, assim como a adição da opção na interface gráfica (mantido o correto funcionamento da funcionalidade).   (Elis e Leo)
Adição de marcadores 3D próximo às regiões de interesse selecionadas pelo usuário. Um marcador pode ser um objeto 3D tal como o exemplo abaixo:
https://www.vectorstock.com/royalty-free-vector/realistic-detailed-3d-red-push-pin-vector-20821752
Para cada região de interesse definida no arquivo xml, deverá ser posicionado o modelo 3D do marcador próximo à região de interesse, como se esse estivesse “espetado” sobre o objeto. 
(Continuação do item 5) Na página de apresentação multimídia deverá ser adicionada uma opção para “mostrar marcadores”. Habilitada essa opção, todos os marcadores deverão ser exibidos junto ao objeto principal. Ao ser desmarcada a opção, o objeto deverá ser exibido sem os marcadores. Além disso, quando o usuário clicar sobre um determinado marcador, a região de interesse deverá ser apresentada (conforme é feito atualmente ao clicar no título da região de interesse na barra lateral). (Eder e Julio)
Atualização da interface gráfica de página de associação 3D para prover uma melhor experiência ao usuário. Atualmente, são utilizadas as tecnologias HTML5 e CSS para construção da interface gráfica. Partes da interface gráfica são criadas automaticamente quando a página é carregada por meio de código JavaScript. Para essa tarefa, também podem ser adicionados outros recursos ou bibliotecas para criação de interfaces interativas. (Giovani e Ricardo)
Atualização da interface gráfica de página de apresentação multimídia para prover uma melhor experiência ao usuário. Atualmente, são utilizadas as tecnologias HTML5 e CSS para construção da interface gráfica. A interface gráfica da página é criada automaticamente a partir do arquivo xml da apresentação. Para essa tarefa, também podem ser adicionados outros recursos ou bibliotecas para criação de interfaces interativas. (Mauricio, Bruno e GuiGui)
Integração das alterações e atualizações desenvolvidas nos itens anteriores, gerando uma única versão da aplicação web (página de associação de dados e página de apresentação multimídia). (Matheus e Gabriel)
Equipes

O projeto deverá ser desenvolvido por equipes de até 3 alunos. Cada equipe deverá escolher uma das contribuições dos itens de 1 a 9.

Entrega

Cada equipe deverá armazenar o seu projeto e dados (arquivos do projeto, página web, modelos 3D, etc) em sua respectiva pasta no drive.

Datas importantes

11/11/19 - Início do projeto
18/11/19 - Aula inteiramente destinada ao desenvolvimento do projeto
25/11/19 - Aula destinada à finalização do projeto
02/12/19 - Entrega e apresentação do projeto
