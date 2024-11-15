# El compilador a utilizar
CC = gcc
# Las banderas de compilación
CFLAGS = -Wall -g -Iinc

# Directorios
OBJ_DIR = obj
SRC_DIR = src
RES_DIR = res
TARGET = CalifiC

# Archivos fuente
SOURCES = main.c $(SRC_DIR)/admin.c $(SRC_DIR)/login.c

# Archivos objeto
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/admin.o $(OBJ_DIR)/login.o

# Archivos de recursos
ICON_RC = $(RES_DIR)/icon.rc
ICON_OBJ = $(OBJ_DIR)/icon.o

# Regla por defecto
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJECTS) $(ICON_OBJ)
	$(CC) -o $@ $^

# Regla para compilar los archivos objeto
$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/admin.o: $(SRC_DIR)/admin.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/login.o: $(SRC_DIR)/login.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar el archivo de recursos icon.rc
$(ICON_OBJ): $(ICON_RC)
	windres $(ICON_RC) -o $(ICON_OBJ)

# Crear el directorio obj si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
	rmdir $(OBJ_DIR) || true  # Ignorar error si el directorio no existe
