// 只是代码段
// 前面需要初始化mSharedMemory，并设置key
void BoardEditorState_SharedCopy::writeSharedMemory() {
    // TODO: 解决死锁问题
    if ( mSharedMemory->isAttached() ) {
        // 与主进程分离
        if ( !mSharedMemory->detach() ) {
            std::cout << mSharedMemory->error() << std::endl;
            std::cout << mSharedMemory->errorString().toStdString() << std::endl;
        }
    }
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << serialize();
    int size = buffer.size();
    // 创建共享内存
    if ( !mSharedMemory->create(size) ) {
        std::cout << mSharedMemory->error() << std::endl;
        std::cout << mSharedMemory->errorString().toStdString() << std::endl;
        // return;
    }
    // 上锁
    mSharedMemory->lock();
    char*       to = (char*)mSharedMemory->data();
    const char* from = buffer.data().data();
    memcpy(to, from, qMin(mSharedMemory->size(), size));
    // 解锁
    mSharedMemory->unlock();
}
void BoardEditorState_SharedCopy::readSharedMemory() {
    // 上锁
    mSharedMemory->lock();
    // 共享内存与主进程绑定
    if ( !mSharedMemory->attach() ) {
        std::cout << mSharedMemory->errorString().toStdString() << std::endl;
    }
    QBuffer     buffer;
    QDataStream in(&buffer);

    buffer.setData((char*)mSharedMemory->constData(), mSharedMemory->size());
    buffer.open(QBuffer::ReadOnly);
    QByteArray bytearray;
    in >> bytearray;
    SExpression se = SExpression::parse(bytearray, FilePath());
    if ( se.tryGetChildByPath("shape") ) {
        SExpression s = se.getChildByPath("shape");
        auto&       board = Holder::getActiveBoard();
        auto*       item = new BI_Shape(board, s);
        board.addItem(item);
    }
    // 解锁
    mSharedMemory->unlock();
    // 与主进程分离
    mSharedMemory->detach();
}