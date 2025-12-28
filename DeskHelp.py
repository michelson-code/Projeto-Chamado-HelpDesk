import random

chamados = []
proximo_sequencial = 1

def gerar_numero_chamado(seq):
    # Gera 5 dígitos aleatórios + 2 dígitos sequenciais
    prefixo = random.randint(10000, 99999)
    sufixo = str(seq).zfill(2)
    return int(f"{prefixo}{sufixo}")

def organizar_lista():
    """Ordena por Prioridade (3->1) e depois por Sequencial (01->99)."""
    global chamados
    chamados.sort(key=lambda c: (-c['prioridade'], c['numero'] % 100))

def abrir_chamado():
    global proximo_sequencial
    numero = gerar_numero_chamado(proximo_sequencial)
    
    print(f"\n[Abertura] Nº do chamado em tela: {numero}")
    nome = input("Nome do usuário: ")
    setor = input("Setor do usuário: ")
    descricao = input("Descrição do problema: ")
    
    # Regra: Prioridade 1 (Baixa) e Status A (Aberto) por padrão
    novo_chamado = {
        "numero": numero,
        "usuario": nome,
        "setor": setor,
        "descricao": descricao,
        "prioridade": 1,
        "status": "A"
    }
    
    chamados.append(novo_chamado)
    proximo_sequencial += 1
    organizar_lista()
    print("Chamado aberto com sucesso!")

def localizar_chamado():
    try:
        num = int(input("\nDigite o nº do chamado para localizar: "))
        for c in chamados:
            if c["numero"] == num:
                exibir_detalhes(c)
                
                # Sub-menu para Encerrar ou Atualizar Prioridade
                print("\nOpções para este chamado:")
                print("A - Atualizar Prioridade | E - Encerrar Chamado | S - Sair")
                op = input("Escolha: ").upper()
                
                if op == 'A':
                    nova = int(input("Nova Prioridade (1-Baixa, 2-Média, 3-Alta): "))
                    if nova in [1, 2, 3]:
                        c["prioridade"] = nova
                        organizar_lista()
                        print("Prioridade atualizada!")
                elif op == 'E':
                    c["status"] = "F" # F para Fechado
                    print("Status alterado para Fechado!")
                return
        print("Chamado não encontrado.")
    except ValueError:
        print("Entrada inválida.")

def excluir_chamado():
    try:
        num = int(input("\nDigite o nº do chamado para EXCLUIR: "))
        for i, c in enumerate(chamados):
            if c["numero"] == num:
                del chamados[i] # Elimina o chamado da lista
                print(f"Chamado {num} excluído permanentemente.")
                return
        print("Chamado não encontrado.")
    except ValueError:
        print("Entrada inválida.")

def imprimir_todos():
    if not chamados:
        print("\nNenhum chamado ativo.")
        return
    
    organizar_lista()
    print("\n" + "="*75)
    print(f"{'SEQ':<4} | {'ID TOTAL':<10} | {'USUÁRIO':<15} | {'PRIORIDADE':<10} | {'STATUS':<10}")
    print("-" * 75)
    
    prio_nomes = {1: "Baixa", 2: "Média", 3: "Alta"}
    status_nomes = {"A": "Aberto", "E": "Em Atend.", "F": "Fechado"}
    
    for c in chamados:
        seq_visual = str(c['numero'])[-2:] # Pega apenas os 2 últimos dígitos
        print(f"{seq_visual:<4} | {c['numero']:<10} | {c['usuario']:<15} | "
              f"{prio_nomes[c['prioridade']]:<10} | {status_nomes[c['status']]:<10}")
    print("="*75)

def exibir_detalhes(c):
    prio_nomes = {1: "Baixa", 2: "Média", 3: "Alta"}
    status_nomes = {"A": "Aberto", "E": "Em Atendimento", "F": "Fechado"}
    print(f"\n--- Detalhes: {c['numero']} ---")
    print(f"Usuário: {c['usuario']} | Setor: {c['setor']}")
    print(f"Descrição: {c['descricao']}")
    print(f"Prioridade: {prio_nomes[c['prioridade']]} | Status: {status_nomes[c['status']]}")

def menu():
    while True:
        print("\n--- MENU HELP DESK ---")
        print("1 - Abrir chamado")
        print("2 - Localizar chamado (por nº)")
        print("3 - Excluir chamado")
        print("4 - Quantidade de chamados (todos)")
        print("5 - Imprimir chamados (todos)")
        print("6 - Sair do sistema")
        
        opcao = input("\nEscolha: ")
        
        if opcao == '1': abrir_chamado()
        elif opcao == '2': localizar_chamado()
        elif opcao == '3': excluir_chamado()
        elif opcao == '4': print(f"\nTotal: {len(chamados)} chamados.")
        elif opcao == '5': imprimir_todos()
        elif opcao == '6': break
        else: print("Opção inválida.")

if __name__ == "__main__":
    menu()