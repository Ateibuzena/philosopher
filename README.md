# Philosopher 🍽️🧠

## 📜 Descripción
**Philosopher** es un proyecto desarrollado en el marco de 42 Málaga, basado en el problema clásico de los "Filósofos comensales" (Dining Philosophers Problem). Este problema es un ejercicio de sincronización utilizado para estudiar la gestión de recursos compartidos en sistemas concurrentes.

En el problema, un grupo de filósofos están sentados alrededor de una mesa redonda. Cada filósofo alterna entre los estados de pensar y comer. Sin embargo, para comer, un filósofo necesita tener acceso exclusivo a dos palillos (uno a la izquierda y otro a la derecha). Este proyecto simula y resuelve este problema utilizando herramientas de programación de bajo nivel, como hilos y semáforos.

## ✨ Características
- 🌀 Simulación del problema de los Filósofos comensales.
- 🧵 Uso de hilos (threads) para implementar la concurrencia.
- 🔒 Gestión de recursos compartidos mediante semáforos o mutexes.
- 🚀 Evitación de condiciones de carrera y deadlocks.

## 🛠️ Requisitos
Para compilar y ejecutar el proyecto, necesitas:
- **Compilador C** (gcc o similar).
- **Make** (para compilar el proyecto).
- Sistema operativo Linux o macOS (opcional, pero recomendado).

## 🚀 Instalación
1. Clona el repositorio:
   ```bash
   git clone https://github.com/Ateibuzena/Philosofer.git
   cd Philosofer
   ``` 
2. Compila el proyecto:
   ```bash
   make
   ```
## 🕹️ Uso
1. Ejecuta el programa desde la terminal:
   ```bash
   ./philo <n_filósofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_pensar> [n_comidas]
   ```
·  <n_filósofos>: Número de filósofos (y palillos).
·  <tiempo_para_morir>: Tiempo en milisegundos antes de que un filósofo muera si no come.
·  <tiempo_para_comer>: Tiempo en milisegundos que tarda un filósofo en comer.
·  <tiempo_para_pensar>: Tiempo en milisegundos que tarda un filósofo en pensar.
·  [n_comidas]: (Opcional) Número de comidas que cada filósofo debe completar antes de que termine la simulación.

2. Observa la simulación en la terminal.

## 📝 Ejemplo
Para ejecutar una simulación con 5 filósofos:
  ```bash
  ./philo 5 800 200 200
  ```
Esto simula 5 filósofos que tienen un tiempo para morir de 800 ms, un tiempo para comer de 200 ms y un tiempo para pensar de 200 ms.

## 📂 Estructura del proyecto
·  src/ : Contiene el código fuente del proyecto.
·  .h : Archivos de cabecera.
·  Makefile : Script de compilación.

## ⚙️ Detalles técnicos

### 🧮 Algoritmos
El proyecto implementa varias estrategias para evitar problemas clásicos como:

·  Interbloqueos (Deadlocks): Se utiliza un orden de adquisición de recursos o soluciones como el uso de un mutex global.
·  Inanición (Starvation): Se asegura que todos los filósofos tengan una oportunidad justa de comer.

### 🛠️ Herramientas usadas
·  Hilos (threads): Para simular a cada filósofo como una tarea concurrente.
·  Semáforos/mutexes: Para controlar el acceso a los recursos compartidos (palillos).

## 👩‍💻 Autor
Ana Zubieta
Proyecto desarrollado en el contexto de 42 Málaga - Fundación Telefónica.

