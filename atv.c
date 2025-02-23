#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} ItemCarrinho;

Produto produtos[MAX_PRODUTOS];  // Array para armazenar produtos cadastrados
ItemCarrinho carrinho[MAX_CARRINHO];  // Array para armazenar produtos no carrinho
int numProdutos = 0;
int numItensCarrinho = 0;

// Declaraçõeses das funçõeses (prototipação)
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
void alterarOuRemoverProduto();
void fecharPedido();
int temNoCarrinho(int codigo);
Produto* pegarProdutoPorCodigo(int codigo);

// Função para exibir o menu principal
void menu() {
    int opcao;
    do {
        printf("\n--- Sistema de Supermercado ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Alterar ou Remover Produto do Carrinho\n");
        printf("6. Fechar Pedido\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: comprarProduto(); break;
            case 4: visualizarCarrinho(); break;
            case 5: alterarOuRemoverProduto(); break;
            case 6: fecharPedido(); break;
            case 7: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 7);
}

// Função para verificar se o produto ja existe com o mesmo codigo
int codigoExistente(int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return 1;  // Produto com esse codigo ja existe
        }
    }
    return 0;  // Codigo unico
}

// Função para cadastrar novos produtos
void cadastrarProduto() {
    if(numProdutos < MAX_PRODUTOS) {
        Produto novoProduto;
        printf("Digite o codigo do produto: ");
        scanf("%d", &novoProduto.codigo);
        
        if (codigoExistente(novoProduto.codigo)) {
            printf("Erro: Produto com codigo %d ja existe!\n", novoProduto.codigo);
            return;
        }

        printf("Digite o nome do produto: ");
        scanf("%s", novoProduto.nome);
        printf("Digite o preco do produto: ");
        scanf("%f", &novoProduto.preco);
        
        produtos[numProdutos++] = novoProduto;
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos cadastrados atingido!\n");
    }
}

// Função para listar todos os produtos cadastrados
void listarProdutos() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado!\n");
    } else {
        printf("\n--- Lista de Produtos ---\n");
        for(int i = 0; i < numProdutos; i++) {
            printf("Codigo: %d, Nome: %s, Preco: %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
        }
    }
}

// Função para buscar produto pelo cÃ³digo
Produto* pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;
}

// Função para verificar se o produto jÃ¡ estÃ¡ no carrinho
int temNoCarrinho(int codigo) {
    for (int i = 0; i < numItensCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Função para adicionar produtos ao carrinho
void comprarProduto() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado. Cadastre um produto antes de comprar.\n");
        return;
    }

    int codigo, quantidade;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    Produto *produto = pegarProdutoPorCodigo(codigo);

    if (produto != NULL) {
        printf("Quantidade: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0) {
            printf("Quantidade invalida!\n");
            return;
        }

        int indiceCarrinho = temNoCarrinho(codigo);
        if (indiceCarrinho != -1) {
            carrinho[indiceCarrinho].quantidade += quantidade;  // Aumenta a quantidade do produto
        } else {
            carrinho[numItensCarrinho].produto = *produto;
            carrinho[numItensCarrinho].quantidade = quantidade;
            numItensCarrinho++;
        }
        printf("Produto adicionado ao carrinho!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }
}

// Funçãoo para visualizar os produtos no carrinho
void visualizarCarrinho() {
    if (numItensCarrinho == 0) {
        printf("Carrinho vazio!\n");
    } else {
        printf("\n--- Carrinho de Compras ---\n");
        for (int i = 0; i < numItensCarrinho; i++) {
            printf("Produto: %s, Quantidade: %d, Preco Unitario: %.2f, Subtotal: %.2f\n",
                   carrinho[i].produto.nome, carrinho[i].quantidade,
                   carrinho[i].produto.preco, carrinho[i].produto.preco * carrinho[i].quantidade);
        }
    }
}

// Funçãoo para alterar a quantidade ou remover um produto do carrinho
void alterarOuRemoverProduto() {
    if (numItensCarrinho == 0) {
        printf("Carrinho vazio!\n");
        return;
    }

    int codigo, novaQuantidade;
    printf("Digite o codigo do produto que deseja alterar/remover: ");
    scanf("%d", &codigo);

    int indiceCarrinho = temNoCarrinho(codigo);
    if (indiceCarrinho != -1) {
        printf("Produto encontrado: %s, Quantidade atual: %d\n", carrinho[indiceCarrinho].produto.nome, carrinho[indiceCarrinho].quantidade);
        printf("Digite a nova quantidade (ou 0 para remover): ");
        scanf("%d", &novaQuantidade);

        if (novaQuantidade > 0) {
            carrinho[indiceCarrinho].quantidade = novaQuantidade;  // Atualiza a quantidade
            printf("Quantidade atualizada!\n");
        } else {
            // Remove o produto do carrinho
            for (int i = indiceCarrinho; i < numItensCarrinho - 1; i++) {
                carrinho[i] = carrinho[i + 1];
            }
            numItensCarrinho--;
            printf("Produto removido do carrinho!\n");
        }
    } else {
        printf("Produto nao encontrado no carrinho!\n");
    }
}

// Função para fechar o pedido
void fecharPedido() {
    if (numItensCarrinho == 0) {
        printf("Carrinho vazio! Adicione produtos antes de fechar o pedido.\n");
        return;
    }

    float total = 0;
    printf("\n--- Fechamento do Pedido ---\n");
    for (int i = 0; i < numItensCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        total += subtotal;
        printf("Produto: %s, Quantidade: %d, Subtotal: %.2f\n", 
               carrinho[i].produto.nome, carrinho[i].quantidade, subtotal);
    }
    printf("Valor total da compra: %.2f\n", total);

    // Esvaziar o carrinho
    numItensCarrinho = 0;
    printf("Pedido finalizado!\n");
}

// Funçao principal para executar o programa
int main() {
    menu();
    return 0;
}