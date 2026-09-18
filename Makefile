CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Имена исполняемых файлов
TARGET = element_program
GENERATOR = generate_bin

# Цель по умолчанию
all: $(TARGET) $(GENERATOR)

# Компиляция основной программы из main.c
$(TARGET): main.c element.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c

# Компиляция генератора из generate_bin.c
$(GENERATOR): generate_bin.c element.h
	$(CC) $(CFLAGS) -o $(GENERATOR) generate_bin.c

# Очистка
clean:
	rm -f $(TARGET) $(GENERATOR) *.bin
	rm -f *.o

# Запуск генератора для создания бинарного файла
run_generator:
	./$(GENERATOR)

# Запуск программы с файлом по умолчанию
run:
	./$(TARGET)

# Запуск программы с конкретным файлом
run_with_file:
	./$(TARGET) elements.bin

# Создать тестовые данные и запустить программу
test: $(GENERATOR) $(TARGET)
	./$(GENERATOR)
	./$(TARGET)

# Пересобрать всё
rebuild: clean all

# Информация о доступных командах
help:
	@echo "Доступные команды:"
	@echo "  make           - скомпилировать программу и генератор"
	@echo "  make clean     - удалить все скомпилированные файлы"
	@echo "  make run       - запустить программу"
	@echo "  make run_generator - запустить генератор"
	@echo "  make test      - создать тестовые данные и запустить программу"
	@echo "  make rebuild   - пересобрать всё заново"

.PHONY: all clean run run_generator run_with_file test rebuild help