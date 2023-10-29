# Nome do executável desejado
TARGET = srtf

# Lista de fontes
SOURCES = pingpong-scheduler-srtf.c ppos-core-aux.c

# Opções do compilador
CC = gcc
CFLAGS = -Wall -std=c99

# Nome da biblioteca estática
LIBRARY = libppos_static.a

# Comando de compilação
$(TARGET): $(SOURCES) $(LIBRARY)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBRARY)

# Regra para criar a biblioteca estática
$(LIBRARY):
	# Comando para criar a biblioteca estática, se necessário
	# Por exemplo: ar rcs $(LIBRARY) arquivo1.o arquivo2.o

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET)

.PHONY: clean