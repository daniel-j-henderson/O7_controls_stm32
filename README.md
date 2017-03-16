# O7_controls_stm32
The software (only the user-defined subset) for the STM32F767ZI microcontroller.

To run software on the controls board, first get the <a href="http://www.st.com/en/embedded-software/stm32cubef7.html"><b>STMCube software</b></a> from the ST website. Then, initialize an empty git repository in the top level directory. Set the remote to this repository and pull the most recent commit to get the newest version of the user-edited files using the commands below. Only user-edited files are stored in the repo, and many other library files are required to run the software. Then, do a file->import, choose Projects/STM32F767ZI-Nucleo/Templates, and select the STM32F767ZI_Nucleo_AXIM_FLASH project when it finds it. You should then be able to successfully import and build the project.

I am working on getting rid of all the extra stuff that comes with the STMCube package (all the unnecessary libraries and example projects), it's just taking a bit to figure out how to get rid of the make rules for that stuff in the IDE. When I get rid of all that, it'll be a more compact directory structure. 


git fetch --all
git reset --hard origin/master
