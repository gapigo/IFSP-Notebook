from random import uniform
from time import sleep
from threading import Thread, Lock

pratos = [0, 0, 0, 0, 0]  # 0 = Não comeu, 1 = Já comeu


class Filosofo(Thread):
    execute = True  # variável para realizar a execução

    def __init__(self, nome, hashi_esquerda, hashi_direita):  # Construtor da classe Filosofo
        Thread.__init__(self)
        self.nome = nome
        self.hashi_esquerda = hashi_esquerda
        self.hashi_direita = hashi_direita

    def run(self):
        """ Sobrescrita de Thread, a função run definirá o que irá acontecer após chamar o método start() na
        instância criada. """
        while self.execute:
            print(f"\n {self.nome} está pensando")
            sleep(uniform(5, 15))
            self.comer()

    def comer(self):
        """
        Pega o hashi 1 e tenta pegar o hashi 2. Se o hashi 2 estiver livre,
        o ele janta e solta os dois hashis em seguida,senão ele desiste de
        comer e continua pensando.
        """
        hashi1, hashi2 = self.hashi_esquerda, self.hashi_direita

        while self.execute:  # enquanto tiver executando
            hashi1.acquire(True)  # tenta pegar o primeiro hashi
            locked = hashi2.acquire(False)  # verifica se o segundo hashi está livre
            if locked:
                break
            hashi1.release()  # libera o hashi1
        else:
            return  # volta a pensar

        print(f"\n {self.nome} começou a comer")
        sleep(uniform(5, 10))
        print(f"\n {self.nome} parou de comer")
        pratos[nomes.index(self.nome)] += 1  # contabiliza o número de vezes que cada filosofo comeu
        print(pratos)
        hashi1.release()  # libera o hashi1
        hashi2.release()  # libera o hashi2


nomes = ['Aristóteles', 'Platão', 'Sócrates', 'Pitágoras', 'Demócrito']  # Nomes dos filósofos
hashis = [Lock() for _ in range(5)]
mesa = [Filosofo(nomes[i], hashis[i % 5], hashis[(i + 1) % 5]) for i in range(5)]
for _ in range(50):
    Filosofo.execute = True  # Inicia a execução
    for filosofo in mesa:
        try:
            filosofo.start()  # inicia o objeto de thread criado.
            sleep(2)
        except RuntimeError:  # Se a thread já tiver sido iniciada
            pass
    sleep(uniform(5, 15))
    Filosofo.execute = False  # Para a execução
   
