cmake_minimum_required(VERSION 3.23)
project(POONatural)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        main.cpp
        Constantes.cpp
        Comandos/Comando.cpp
        Comandos/CriaAnimal.cpp
        Comandos/Food.cpp
        Comandos/Slide.cpp
        Comandos/Exit.cpp
        Comandos/Next.cpp
        Comandos/Anim.cpp
        Comandos/Visanim.cpp
        Comandos/Killid.cpp
        Comandos/Nofood.cpp
        Comandos/Info.cpp
        Comandos/Store.cpp
        Comandos/Restore.cpp
        Comandos/Load.cpp
        Comandos/Kill.cpp
        Comandos/Empty.cpp
        Comandos/See.cpp
        Comandos/Feedid.cpp
        Comandos/Feed.cpp
        Alimentos/Alimento.cpp
        Alimentos/Bife.cpp
        Alimentos/Corpo.cpp
        Alimentos/Cenoura.cpp
        Alimentos/Relva.cpp
        Animais/Animal.cpp
        Animais/Ovelha.cpp
        Reserva/Reserva.cpp
        Reserva/Local.cpp
        Interfaces/Interface.cpp
        Interfaces/Save.cpp
        Terminal.cpp
        Alimentos/Banana.cpp
        )
target_link_libraries(${PROJECT_NAME} C:/pdcurses/pdcurses.a)