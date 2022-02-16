'''
ENTRADAS
--------
num_endnodes : Quantidade de nós finais
slots_per_slotframe : Quantidade de slots por slotframe
slot_duration : Duração de um slot de tempo em ms
slot_nodes : Nós relacionados aos slots
loss_rates : Taxa de perda de pacotes de cada enlace do sorvedouro
'''

num_endnodes = int(input())
slots_per_slotframe = int(input())
slot_duration = float(input())
slot_nodes = input()
loss_rates = [float(input()) for __ in range(num_endnodes)]

slotframe_duration = slots_per_slotframe * slot_duration
slotframes_per_second = 1000 / slotframe_duration

sorvedouro_packets_per_second = []
for endnode in range(1, num_endnodes + 1):
    endnode_packets_per_second = (
        slot_nodes.count(str(endnode)) * slotframes_per_second
    )
    link_packet_loss = endnode_packets_per_second * loss_rates[endnode - 1]

    sorvedouro_packets_per_second.append(
        endnode_packets_per_second - link_packet_loss
    )

for packet_rate in sorvedouro_packets_per_second:
    print(packet_rate)
