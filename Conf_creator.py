import os
import sys


energy_det = [["ALICE_PHOS", [0.018, 0.033, 0.011]],
              ["ALICE3_ECAL_v1", [0.005, 0.025, 0.01]],
              ["ALICE3_ECAL_v2", [0.002, 0.02, 0.01]],
              ["ALICE_EMCAL", [0.029, 0.095, 0.014]]]

momentum_det = [["ALICE_ITS_AND_TPC", [0.008, 0.002]],
                ["ALICE3_TRACKER_V1", [0.015, 0.]],
                ["ALICE3_TRACKER_V2", [0.02, 0.]],
                ["ALICE3_TRACKER_V3", [0.03, 0.]]]


def main(str):
    print(str)

    conf_file_content = ""

    par_names = ["a_e", "b_e", "c_e", "a_m", "b_m"]

    """for i in energy_det:
        if i[0] in str:
            for k in range(len(i[1])):
                conf_file_content += par_names[k] + " = " + str(i[1][k]) + "\n"
            for j in momentum_det:
                if j[0] in str:
                    for l in range(len(j[1])):
                        conf_file_content += par_names[l + 3] + " = " + str(j[1][l]) + "\n"
                    print(i[0], " and ", j[0], " in ", str)
                    f = open("config_parameters.conf", "w")
                    f.write(conf_file_content)
                    f.close()"""

if __name__ == '__main__':
    if len(sys.argv) == 1:
        main("ALICE_PHOS_and_ALICE_ITS_AND_TPC")
    else:
        main(sys.argv[1])

