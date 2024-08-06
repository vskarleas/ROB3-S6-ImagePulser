#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;36m'
PURPLE='\033[1;35m'
YELLOW='\033[0;33m'
NORMAL='\033[0m'  # Define NORMAL as reset (in ASNI) 

clear

# Print a message to the user
echo -e "${BLUE}Welcome to the ImagePulser from Vasileios Filippos Skarleas, Evanthia Virginia Anastasopoulou and Yanis Sadoun. Once you are ready to start exploring the capabilities of the software simply press ENTER"
echo -e "${GREEN}Bienvenue dans le ImagePulser de Vasileios Filippos Skarleas, Evanthia Virginia Anastasopoulou and Yanis Sadoun. Une fois que vous êtes prêt à commencer de decouvrir le logiciel, appuyez simplement sur ENTER"

# Read a line of input from the user
read input

# If the user presses Enter, run the specified commands
if [[ -n "$input" ]]; then
  echo -e "${PURPLE}You did not press ENTER and the program will terminate"
else
  # Run the initial commands
  clear
  echo -e "${PURPLE}Initialising environment..."
  sleep 2
  make clean
  make
  clear
  echo -e "${NORMAL}This software allows you to capture an image and then apply different simplification techniques on the captured image.\n"
  echo -e "${BLUE}NOTE:${NORMAL} In order to implement tests, manually or automaticly then follow the instructions mentioned at https://github.com/vskarleas/ROB3-S6-ImagePulser.\n"
  echo -e "${PURPLE}Please make sure that you have set the correct camera port on line 154 at image_capture.cpp and that you have up and running the arduino code for controling the camera position by using the arrow keys.${NORMAL}\n"
  echo -e "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

  # Infinite loop with user options
  while true; do
    echo -e "\n- auto: Runs the default workflow for the software."
    echo -e "- manual: Allows you to manually choose a PBM image and process it using any of the options provided on the program (segments, bezier2 or bezier3)."
    echo -e "- exit: Exits the program."
    echo -e "${BLUE}========================================================\n${NORMAL}Enter a command (auto, manual, exit):"
    read command

    case "$command" in
      auto)
        clear
        ./ui
        ;;
      manual)
        clear
        while true; do
          echo -e "\n==========================================================\n${GREEN}What do you want to do ?${NORMAL}\n\nYou can visualise the available images for testing porpuses via show_images shows images in PBM format - the only format on which we can apply the algorith simplifications).\n\n${BLUE}Feel free to place images inside the images folder and use teh command process in order to tranform it PBM.${NORMAL}\nThen you can choose any of the following options: segments, bezier2 or bezier3.\n\nYou have also the option to Cartoonize the image and use it in combination with a siplification method. Simply tap cartoon and then show_images to verify that the image has been passed into a PBM format.\n\nYou can exit the manual mode by taping stop:"
          read command

          case "$command" in
            show_images)
              echo -e "\nThere you go:"
              echo -e "------------------"
              ls pbms
              sleep 1
              ;;
            process)
              clear
              ./image_processing_manual
              sleep 1
              ;;
            cartoon)
              clear
              ./cartoon_manual
              echo -e "\nNow do not forget to put the image on PBM format if you want to use it for simplification. Use the command process"
              sleep 1
              ;;
            segments)
              clear
              ./segments_simplification_manual
              sleep 1
              ;;
            bezier3)
              clear
              ./bezier3_simplification_manual
              sleep 1
              ;;
            bezier2)
              clear
              ./bezier2_simplification_manual
              sleep 1
              ;;
            stop)
              break  # Exit the loop
              ;;
            *)
              echo -e "${YELLOW}\nInvalid selection. Please try again!${NORMAL}"
              ;;
          esac
        done
        clear
        echo -e "You have exited the manual mode."
        ;;
      exit)
        break  # Exit the loop
        ;;
      *)
        echo -e "${YELLOW}\nInvalid command. Please try again!${NORMAL}"
        ;;
    esac
  done

  # Commands to execute after exiting the loop
  make clean
  clear
  echo -e "${GREEN}ImagePulser has been successfully terminated\n"
  echo -e "${NORMAL}Thank you! | ${BLUE}Copyright © 2023 - $(date +%Y) ${NORMAL} Vasileios Filippos Skarleas, Yanis Sadoun, Evanthia Virginia Anastasopoulou - All rights reserved"
fi
