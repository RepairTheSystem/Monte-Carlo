# Метод Монте Карло

Благодаря методу реализовано вычисления числа пи по такому принципу:
Точки генерируются внутри единичного квадрата и проверяется их нахождение внутри окружности. 
Введется учет точек, попавших в окружность, что влияет на итоговую вероятность и оценки.

Пользовательский ввод ожидает количество точек для проведения эксперимента.

Количество потоков определеяется как наиболее оптимальное для конкретного устройства.
Общее количество точек, которое нужно сгенерировать и проверить, делится на количество потоков. Таким образом, каждый поток обрабатывает свою порцию точек. Потоки синхронизируются мьютексами.
