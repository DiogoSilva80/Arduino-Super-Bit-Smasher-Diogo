**Título Sugerido**
Super Bit Smasher (Arduino) | Jogo Lógico Bitwise

**Descrição para o README do GitHub**
O Super Bit Smasher é um jogo desenvolvido para a plataforma Arduino que tem como objetivo transformar um valor inicial num valor alvo através de operações lógicas *bitwise* (AND, OR, XOR). O sistema requer rigor na manipulação de bits, combinando lógica de programação com controlo de tempo e integração física de hardware.

**Mecânicas e Funcionalidades**

* **Operações Condicionais:** O sistema gera valores aleatórios de 8 bits para o estado inicial e para o alvo (`target`) no início de cada ronda. A disponibilidade da operação AND requer que o bit 1 do valor alvo esteja ativo, enquanto a operação XOR exige que o bit 1 esteja inativo. A operação OR está sempre disponível para uso.


* **Gestão de Tempo e LEDs:** O jogador dispõe de um limite de 10 segundos para concluir cada ronda. O tempo restante é sinalizado dinamicamente por LEDs, em que cada LED corresponde a 25% do tempo disponível. Ao esgotar-se o tempo, todos os LEDs acendem e a ronda é imediatamente encerrada.


* **Interação e Debouncing:** A interação é feita através do monitor série para inserção de valores e através de botões físicos para a seleção das operações. A leitura dos botões é processada pela função `isButtonPressed()`, que utiliza `millis()` para aplicar *debouncing* e ignorar entradas duplicadas. Pressionar o botão OR durante mais de 2 segundos reinicia o jogo, uma duração também monitorizada via `millis()`.



**Arquitetura do Código**
O programa encontra-se modularizado e organizado com estruturas de controlo (`if`, `else` e ciclos) para validação de entradas e execução lógica:

* **`startGame`:** Inicializa e configura os parâmetros de uma nova ronda.


* **`generateRandom8Bit`:** Processa a criação dos valores operacionais de 8 bits.


* **`updateLeds` e `resetLeds`:** Atualizam ou apagam o *display* de LEDs consoante o estado temporal da ronda.
