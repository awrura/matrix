![Static Badge](https://img.shields.io/badge/platformio-6.1.16-blue?logo=platformio)
![Static Badge](https://img.shields.io/badge/mqtt-2.0.18-blue?logo=mqtt)
![Static Badge](https://img.shields.io/badge/docker-25.0.4-blue?logo=docker)

# Клиент матрицы

Представляет собой приложение для управления сведоидодами на адресной светодиодной ленте. Управление осуществляется посредством сообщений полученных из `mqtt` броекра

## Аппаратное обеспечение

- [Плата Wemos D1 mini esp8266](https://giant4.ru/catalog/controller/wemos-d1/)
- [Светодиодная лента WS2812B](https://sl.aliexpress.ru/p?key=NHXG39D)
- [Блок питания](https://giant4.ru/catalog/bloki_pitaniya_5v/60w-ip20-5v/)

## Сборка

Сборка происходит при помощи [platformio](https://platformio.org/). **Важно**, перед сборкой приложения необходимо создать `.env` файл и заполнить его переменными окружения. Пример файла окружения можно посмотерть в [.env.example](https://github.com/awrura/matrix/blob/main/.env.example).
После чего можно собрать приложение командой
```bash
platformio run
```

Так же возможна сборка в `docker`. Для этого написан [Dockerfile](https://github.com/awrura/matrix/blob/main/docker/Dockerfile)

## Жизненный цикл

При запуске приложения, контроллер подключается к `mqtt` брокеру и ожидает входящих сообщений. Сообщение представляет собой набор байтов, где каждая позиция байта обусловлена его семантикой. Так например, первым байтом идет **код команды** (допустим _рисование_ или _установка яркости_). После чего идут байты, несущие основную информацию для данной команды. 

Далее производится бизнес логика (допустим рисование изображения на матрице), и далее приложения снова начинает ожидать новых сообщений.

![image](https://github.com/user-attachments/assets/bd4018b9-e7fc-4140-9a9e-bb44c3c3507c)
