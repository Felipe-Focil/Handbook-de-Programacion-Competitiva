# Guía Básica de Git para Contribuir a Proyectos Open Source

Esta guía te ayudará a empezar con Git para contribuir a este proyecto de código abierto en GitHub. Aprenderás desde la instalación hasta cómo hacer un Pull Request. Git es una herramienta poderosa, pero con la práctica se vuelve sencilla de utilizar.

## 1. ¿Qué es Git?
Git es un sistema de control de versiones que permite trabajar de manera colaborativa en proyectos de software. Con él, puedes mantener un historial de cambios, revertir errores, y colaborar con otros de manera eficiente.

## 2. Instalación de Git
Primero, debes instalar [Git](https://git-scm.com/downloads) en tu computadora.

### En Windows:
1. Descarga Git desde: [git-scm.com](https://git-scm.com/download/win).
2. Ejecuta el instalador y sigue las instrucciones.
3. Abre Git Bash para ejecutar comandos de Git.

### En macOS:
1. Abre la terminal y ejecuta:
```bash
brew install git
```

### En Linux (Ubuntu):
1. Abre la terminal y ejecuta:
```bash
sudo apt update
sudo apt install git
```
Para verificar la instalación, ejecuta:
```bash
git --version
```

## 3. Configuración Inicial de Git

Configura tu nombre y correo electrónico para identificar tus cambios:

```bash
git config --global user.name "Tu Nombre"
```
```bash
git config --global user.email "tuemail@example.com"
```

Configura tu editor de texto predeterminado (en este caso, Visual Studio Code):

```bash
git config --global core.editor "code --wait"
```

Para asegurarte de que los saltos de línea sean consistentes:

### En Windows:
```bash
git config --global core.autocrlf true
```

### En Linux/macOS:
```bash
git config --global core.autocrlf input
```

## 4. Inicializar un Repositorio

### Crear una Carpeta de Trabajo
Crea una carpeta en tu computadora para trabajar en el proyecto y accede a ella desde la terminal:
```bash
cd /ruta/a/tu/carpeta
```

### Crear un Repositorio Local
Para crear el repositorio en tu máquina:
```bash
git init
```

Conecta tu repositorio local con GitHub:
```bash
git remote add origin https://github.com/usuario/proyecto.git
```

Actualiza tu repositorio local con los últimos cambios de la rama principal:
```bash
git pull origin main
```

## 5. No Trabajes en la Rama Principal

**Nunca trabajes directamente en la rama principal (`main`)**. Esto previene conflictos y evita que accidentalmente modifiques código importante. Para cada nueva funcionalidad o corrección, crea una rama nueva.

### Crear una Rama
Crea una rama nueva con el siguiente comando:

```bash
git checkout -b mi-rama
```

Sigue una convención de nombres para las ramas: '[nombre-funcionalidad]/[fase]'. Ejemplo:

```bash
git checkout -b A+B/Especificacion
```

## 6. Añadir Cambios

Una vez que realices modificaciones en tu proyecto, verifica qué archivos has cambiado con:
```bash
git status
```

Añade los archivos modificados con:
```bash
git add archivo.txt
```

Si quieres agregar todos los archivos modificados (aunque se recomienda hacerlo con precaución):
```bash
git add .
```

## 7. Hacer un Commit

Después de añadir los archivos, guarda los cambios en el repositorio local con un mensaje descriptivo:
```bash
git commit -m "Descripción breve de los cambios"
```

## 8. Subir Cambios al Repositorio Remoto

Sube los cambios a GitHub con el siguiente comando:
```bash
git push
```

Si es la primera vez que subes una rama nueva:
```bash
git push -u origin mi-rama
```

## 9. Crear un Pull Request

Después de subir los cambios a GitHub, ve a la sección de Pull Requests en GitHub y crea un nuevo PR. Usa un título claro como '[Funcionalidad] Fase' y describe los cambios.

## 10. Actualizar tu Repositorio Local

Mantén tu repositorio local actualizado con los últimos cambios en la rama principal:
```bash
git pull origin main
```

Recuerda que Git es una herramienta que se aprende con la práctica. No dudes en buscar más recursos o pedir ayuda si lo necesitas.

