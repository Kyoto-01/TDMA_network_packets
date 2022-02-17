#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SORVEDOURO_NODE 0

typedef struct {

    float packets_per_second;
    float packet_loss;

} Link;

Link* get_links_infos(int num_links, char* slots, float* loss_rates, float slotframes_per_second){

    // retorna a quantidade de pacotes enviados e perdidos pra cada enlace
    // individual da rede

    Link* links_infos = (Link*)malloc(num_links * sizeof(Link));
    memset(links_infos, 0, num_links * sizeof(links_infos[0]));

    for (int i = 0; i < strlen(slots); i++){
        int endnode = slots[i] - '0';

        if (endnode != SORVEDOURO_NODE){
            links_infos[endnode - 1].packets_per_second += slotframes_per_second;
            links_infos[endnode - 1].packet_loss += slotframes_per_second * loss_rates[endnode - 1];
        }
    }

    return links_infos;
}

float* get_sorvedouro_links_packets_per_second(int num_links, Link* links_infos){

    // retorna a quantidade de pacotes por segundo recebidos em cada
    // enlace do sorvedouro, levando em conta os pacotes perdidos
    
    float* sorvedouro_packets_per_second = (float*)malloc(num_links * sizeof(Link));
    
    for (int i = 0; i < num_links; i++){
        sorvedouro_packets_per_second[i] = links_infos[i].packets_per_second - links_infos[i].packet_loss;
    }

    return sorvedouro_packets_per_second;
}

int main(){
   
    // Entradas

    int num_endnodes = 0;
    int slots_per_slotframe = 0;
    float slot_duration = 0;

    scanf("%d", &num_endnodes);
    scanf("%d", &slots_per_slotframe);
    scanf("%f", &slot_duration);

    char slot_nodes[slots_per_slotframe];
    scanf("%s", slot_nodes);

    float loss_rates[num_endnodes];
    for (int i = 0; i < num_endnodes; i++){
        scanf("%f", &loss_rates[i]);
    }

    // Fim das entradas
    
    float slotframe_duration = slots_per_slotframe * slot_duration;
    float slotframes_per_second = 1000 / slotframe_duration;

    Link* links_infos = get_links_infos(num_endnodes, slot_nodes, loss_rates, slotframes_per_second);
    float* sorvedouro_links_packets_per_second = get_sorvedouro_links_packets_per_second(num_endnodes, links_infos);

    // Saída

    printf("\n-------------------------------------\n");
    for (int i = 0; i < num_endnodes; i++){
        printf("%.1f\n", sorvedouro_links_packets_per_second[i]);
    }

    return 0;
}
