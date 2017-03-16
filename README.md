# O7_controls_stm32
The software (only the user-defined subset) for the STM32F767ZI microcontroller.

To run software on the controls board, first get the <a href="http://www.st.com/en/embedded-software/stm32cubef7.html"><b>STMCube software</b></a> from the ST website. Then, initialize an empty git repository in the top level directory. Set the remote to this repository and pull the most recent commit to get the newest version of the user-edited files using the commands below. Only user-edited files are stored in the repo, and many other library files are required to run the software.


git fetch --all
git reset --hard origin/master
