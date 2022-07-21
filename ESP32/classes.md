# main

- (button_base): инициализация GPIO для кнопки
- (led_base): инициализация ленты, запуск ledEventLoop, создание экземпляров классов эффектов
- LedEventLoop (led_event_loop): обработчик событий задачи LED
- (main): точка входа
- (net_base): инициализация и запуск сетевой подсистемы и httpServer

# effects

- LedEffect (led_effect): виртуальный базовый класс всех эффектов
  - ChristmasTreeEffect (christmas_tree_effect): елка
  - DebugEffect (debug_effect): отладочный эффект для проверки работы с WiFi
  - FireEffect (fire_effect): огонь, не доделан
  - StarsEffect (stars_effect): мигающие звезды
  - TestEffect (test_effect): проверки работы ленты

# http_server

- (hs_simple_effects): обработчики API выбора эффектов (todo: переделать в наследника UriHandler)
- (hs_test_led): обработчики API тестовых еффектов (todo: переделать в наследника UriHandler)
- HttpServer (http_server): класс сервера
- UriHandler (uri_handler): базовый класс обработчика URI (пока не внедрен)
