import pandas as pd
import json


class Robot:
    def __init__(self):
        with open("dim_robot.json") as json_dim_robot:
            self.dim_robot = json.load(json_dim_robot)
            self.size_robot = self.dim_robot["size_robot"][0]
            self.couple_statique = self.dim_robot["couple_motor_statique"][0]
            self.couple_dynamique = self.dim_robot["couple_motor_dynamique"][0]
        self.df_size_robot = pd.DataFrame(data=self.size_robot)
        self.df_couple_statique = pd.DataFrame(data=self.couple_statique)
        self.df_couple_dynamique = pd.DataFrame(data=self.couple_dynamique)

    def changeLength(self, num_arm, value):
        self.dim_robot["size_robot"][0][f"length_arm{num_arm}"] = value
        with open("dim_robot.json", "w") as jsonFile:
            json.dump(self.dim_robot, jsonFile)
        self.df_size_robot[f"length_arm{num_arm}"] = value

    def changeWeightArm(self, num_arm, value):
        self.dim_robot["size_robot"][0][f"weight_arm{num_arm}"] = value
        with open("dim_robot.json", "w") as jsonFile:
            json.dump(self.dim_robot, jsonFile)
        self.df_size_robot[f"weight_arm{num_arm}"] = value

    def changeWeightMotor(self, num_motor, value):
        self.dim_robot["size_robot"][0][f"weight_motor{num_motor}"] = value
        with open("dim_robot.json", "w") as jsonFile:
            json.dump(self.dim_robot, jsonFile)
        self.df_size_robot[f"weight_motor{num_motor}"] = value

    def couplePince(self, masse, coeff_frottement):
        g = 9.81
        strength = (masse * g) / (2 * coeff_frottement)
        self.df_couple_statique["coupleM6"] = (
            strength * self.df_size_robot["length_gripper"]
        )

    def coupleStatique(self):
        self.df_couple_statique["coupleM2"] = (
            self.df_size_robot["length_arm2"] * self.df_size_robot["weight_motor3"]
            + (self.df_size_robot["length_arm2"] + self.df_size_robot["length_arm3"])
            * (
                self.df_size_robot["weight_motor4"]
                + self.df_size_robot["weight_motor5"]
            )
            + (
                self.df_size_robot["length_arm2"]
                + self.df_size_robot["length_arm3"]
                + self.df_size_robot["length_arm5"]
            )
            * self.df_size_robot["weight_motor6"]
            + (self.df_size_robot["length_arm2"] / 2)
            * self.df_size_robot["weight_arm2"]
            + (self.df_size_robot["length_arm3"] / 2)
            * self.df_size_robot["weight_arm3"]
            + (
                self.df_size_robot["length_arm2"]
                + self.df_size_robot["length_arm3"]
                + self.df_size_robot["length_arm5"]
                + self.df_size_robot["length_gripper"] / 2
            )
            * self.df_size_robot["weight_gripper"]
            + (
                self.df_size_robot["length_arm2"]
                + self.df_size_robot["length_arm3"]
                + self.df_size_robot["length_arm5"]
                + self.df_size_robot["length_gripper"]
            )
            * self.df_size_robot["weight_gripper"]
        )
        self.df_couple_statique["coupleM3"] = self.df_couple_statique["coupleM2"] - (
            self.df_size_robot["length_arm2"] * self.df_size_robot["weight_motor3"]
            + (self.df_size_robot["length_arm2"] / 2)
            * self.df_size_robot["weight_arm2"]
        )
        self.df_couple_statique["coupleM4"] = (
            self.df_size_robot["length_arm5"] * self.df_size_robot["weight_gripper"]
            + self.df_size_robot["length_arm5"] / 2 * self.df_size_robot["weight_arm5"]
            + (
                self.df_size_robot["length_arm5"]
                + self.df_size_robot["length_gripper"] / 2
            )
            * self.df_size_robot["weight_gripper"]
            + (self.df_size_robot["length_arm5"] + self.df_size_robot["length_gripper"])
            * self.df_size_robot["weight_gripper"]
        )

    def coupleDynamique(self, num_motor, inertie, acceleration, couple_resistif):
        self.df_couple_dynamique[f"couple{num_motor}"] = (
            inertie * acceleration - couple_resistif
        )


if __name__ == "__main__":
    robot1 = Robot()
    robot1.changeLength(2, 6)
    robot1.changeLength(3, 4)
    robot1.changeLength(4, 2)
    robot1.changeLength(5, 1)
    robot1.changeWeightArm(1, 2)
    robot1.changeWeightArm(2, 4)
    robot1.changeWeightArm(3, 3)
    robot1.changeWeightArm(4, 3)
    robot1.changeWeightArm(5, 1)
    robot1.changeWeightMotor(1, 3)
    robot1.changeWeightMotor(2, 4)
    robot1.changeWeightMotor(3, 5)
    robot1.changeWeightMotor(4, 7)
    robot1.changeWeightMotor(5, 1)
    pd.set_option("display.max_columns", None)
    print(robot1.df_size_robot)
    robot1.coupleStatique()
    print(robot1.df_couple_statique)
