from threading import Thread, Lock

nomes = ['Aristóteles', 'Platão', 'Sócrates', 'Pitágoras', 'Demócrito']  # Nomes dos filósofos
hashis = [Lock() for _ in range(5)]
print([(nomes[i], hashis[i % 5], hashis[(i + 1) % 5]) for i in range(5)])


