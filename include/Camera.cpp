#include "Camera.h"

Camera::Camera(QObject* parent):m_lookSpeed(0.1),m_moveSpeed(0.1)
{
}

Camera::~Camera()
{
}

void Camera::look(float yaw, float pitch, float roll)
{
	m_yaw += yaw;
	while (m_yaw >= 360)
		m_yaw -= 360;
	while (m_yaw < 0)
		m_yaw += 360;
	m_pitch += pitch;
	if (m_pitch > 89)
		m_pitch = 89;
	if (m_pitch < -89)
		m_pitch = -89;
	{
		QVector3D _front{ 0,0,-1 };
		QMatrix4x4 _mat;
		_mat.setToIdentity();
		_mat.rotate(m_pitch, 1, 0, 0);
		_mat.rotate(m_yaw, 0, 1, 0);
		m_front = _front * _mat;
	}
}


void Camera::move(float x, float y, float z)
{
	auto _right = QVector3D::crossProduct(m_front, m_up).normalized();
	auto _front = QVector3D::crossProduct(m_up, _right).normalized();
	m_pos += _front * x;
	m_pos += _right * y;
	m_pos += m_up * z;
}


void Camera::update()
{
	auto _move = m_move.normalized() * m_moveSpeed;
	move(_move.x(), _move.y(), _move.z());

	m_view.setToIdentity();
	//m_pos: QVector3D(0, 3, 6) m_pos + m_front: QVector3D(0.0150375, 2.49246, 5.1385) m_up: QVector3D(0, 1, 0)
	//qDebug() << "m_pos:" << m_pos << "m_pos + m_front:" << m_pos + m_front << "m_up:" << m_up;
	m_view.lookAt(QVector3D(0, 3, 6), QVector3D(0, 2.5, 5), m_up);
	//m_view.lookAt(QVector3D(6+ m_posMany.y(), 0, 0), QVector3D(0, 0, 0), m_up);
	//m_view.lookAt(QVector3D(6, 0, 0), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
}


bool Camera::eventFilter(QObject* obj, QEvent* ev)
{
	auto _widget = qobject_cast<QOpenGLWidget*>(obj);
	if (_widget)
	{
		if (ev->type() == QEvent::KeyPress)
		{
			auto event = static_cast<QKeyEvent*>(ev);
			if (event->key() == Qt::Key_Escape)
			{
				_widget->setMouseTracking(false);
				_widget->setCursor(Qt::ArrowCursor);
			}
			else if (event->key() == Qt::Key_W)
			{
				m_move.setX(1);
			}
			else if (event->key() == Qt::Key_S)
			{
				m_move.setX(-1);
			}
			else if (event->key() == Qt::Key_A)
			{
				m_move.setY(-1);
			}
			else if (event->key() == Qt::Key_D)
			{
				m_move.setY(1);
			}
			else if (event->key() == Qt::Key_Space)
			{
				m_move.setZ(1);
			}
			else if (event->key() == Qt::Key_C)
			{
				m_move.setZ(-1);
			}
		}
		else if (ev->type() == QEvent::KeyRelease)
		{
			auto event = static_cast<QKeyEvent*>(ev);
			if (event->key() == Qt::Key_W)
			{
				m_move.setX(0);
			}
			else if (event->key() == Qt::Key_S)
			{
				m_move.setX(0);
			}
			else if (event->key() == Qt::Key_A)
			{
				m_move.setY(0);
			}
			else if (event->key() == Qt::Key_D)
			{
				m_move.setY(0);
			}
			else if (event->key() == Qt::Key_Space)
			{
				m_move.setZ(0);
			}
			else if (event->key() == Qt::Key_C)
			{
				m_move.setZ(0);
			}
		}
		else if (ev->type() == QEvent::MouseButtonPress && m_bool)
		{
			auto _lastPos = _widget->mapToGlobal(_widget->rect().center());
			//QCursor::setPos(_lastPos);

			_widget->setMouseTracking(true);
			//_widget->setCursor(Qt::BlankCursor);
		}
		else if (ev->type() == QEvent::MouseMove && m_bool)
		{
			//auto event = static_cast<QMouseEvent*>(ev);
			//auto _lastPos = _widget->mapToGlobal(_widget->rect().center());
			//QCursor::setPos(_lastPos);
			////auto _lastPos = event->globalPos();

			////qDebug() << "_lastPos:" << _lastPos;
			////qDebug() << "event->globalPos():" << event->globalPos();
			//auto _move = event->globalPos() - _lastPos;
			////QCursor::setPos(event->globalPos());
			////qDebug() << "_move:" << _move;
			//look(-_move.x() * m_lookSpeed, -_move.y() * m_lookSpeed, 0);

			auto event = static_cast<QMouseEvent*>(ev);
			look(-m_posMany.x() * m_lookSpeed, -m_posMany.y() * m_lookSpeed, 0);
		}
		else if (ev->type() == QEvent::Leave)
		{
			_widget->setMouseTracking(false);
			_widget->setCursor(Qt::ArrowCursor);
		}

	}
	return false;
}

