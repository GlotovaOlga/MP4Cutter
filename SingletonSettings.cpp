#include "SingletonSettings.h"

SingletonSettings& SingletonSettings::getInstance() {
	static SingletonSettings instance;
	return instance;
}


void SingletonSettings::setPeriodTime(uint32_t begTime, uint32_t endTime) {
	m_beginTime = begTime;
	m_endTime = endTime;
    m_newDuration = endTime - begTime;
    m_idBeginChunkVideo = m_beginTime * m_deltaVideo;
    m_idEndChunkVideo = m_endTime * m_deltaVideo;
    m_idBegChunkWithIFrame = m_beginTime * m_deltaIFrame;
    m_idEndChunkWithIFrame = m_endTime * m_deltaIFrame;
    double endIntPart;
    double startIntPart;

    double fractStartPos = modf(((begTime * static_cast<float>(m_timeScaleAudio))/m_deltaAudio)/4.0f,&startIntPart);
    double fractEndPos = modf(((endTime * static_cast<float>(m_timeScaleAudio))/m_deltaAudio)/4.0f,&endIntPart);

    m_idBeginChunkAudio = static_cast<uint32_t>(startIntPart);
    m_idEndChunkAudio = static_cast<uint32_t>(endIntPart);
    m_offsetStartAudioPos = getOffsetAudioChunk(fractStartPos);
    m_offsetEndtAudioPos = getOffsetAudioChunk(fractEndPos);
}

uint32_t SingletonSettings::getBeginTime() {
	return m_beginTime;
}

uint32_t SingletonSettings::getEndTime() {
    return m_endTime;
}

uint32_t SingletonSettings::getNewDuration() const
{
    return m_newDuration;
}

void SingletonSettings::setTimeScaleAudio(uint32_t timeScale) {
    m_timeScaleAudio = timeScale;
}

void SingletonSettings::setTimeScaleVideo(uint32_t timeScale) {
    m_timeScaleVideo = timeScale;
}

uint32_t SingletonSettings::getTimeScaleAudio() {
    return m_timeScaleAudio;
}

uint32_t SingletonSettings::getTimeScaleVideo() {
    return m_timeScaleVideo;
}

void SingletonSettings::setDeltaAudio(uint32_t delta) {
	m_deltaAudio = delta;
}

void SingletonSettings::setDeltaVideo(uint32_t delta) {
    m_deltaVideo = delta;
}

void SingletonSettings::setDeltaIFrame(uint32_t delta)
{
    m_deltaIFrame = delta;
}

uint32_t SingletonSettings::getDeltaAudio() const {
	return m_deltaAudio;	
}

uint32_t SingletonSettings::getDeltaVideo() const {
    return m_deltaVideo;
}

uint32_t SingletonSettings::getDeltaIFrame() const
{
    return m_deltaIFrame;
}

void SingletonSettings::setBeginOffsetAudio(uint32_t offset) {
	m_beginOffsetAudio = offset;
}

void SingletonSettings::setEndOffsetAudio(uint32_t offset) {
	m_endOffsetAudio = offset;
}

void SingletonSettings::setBeginOffsetVideo(uint32_t offset) {
	m_beginOffsetVideo = offset;
}

void SingletonSettings::setEndOffsetVideo(uint32_t offset) {
    m_endOffsetVideo = offset;
}

std::pair<uint32_t, uint32_t> SingletonSettings::getOffsetAudio()
{
    return std::pair<uint32_t, uint32_t>(m_beginOffsetAudio,m_endOffsetAudio);
}

std::pair<uint32_t, uint32_t> SingletonSettings::getOffsetVideo()
{
    return std::pair<uint32_t, uint32_t>(m_beginOffsetVideo,m_endOffsetVideo);
}

std::pair<uint32_t, uint32_t> SingletonSettings::getStartIdChunkAudio()
{
    return std::pair<uint32_t, uint32_t>(m_idBeginChunkAudio,m_offsetStartAudioPos);
}

std::pair<uint32_t, uint32_t> SingletonSettings::getEndIdChunkAudio()
{
    return std::pair<uint32_t, uint32_t>(m_idEndChunkAudio,m_offsetEndtAudioPos);
}

void SingletonSettings::setArrayChunkOffsetAudio(std::vector<uint32_t> &arrayChunkOffset) {
	pm_chunkOffsetAudio = &arrayChunkOffset;
}

void SingletonSettings::setArrayChunkOffsetVideo(std::vector<uint32_t> &arrayChunkOffset) {
    pm_chunkOffsetVideo = &arrayChunkOffset;
}

std::vector<uint32_t>& SingletonSettings::getArrayChunkOffsetAudio() {
	return *pm_chunkOffsetAudio;
}

std::vector<uint32_t>& SingletonSettings::getArrayChunkOffsetVideo() {
	return *pm_chunkOffsetVideo;
}


void SingletonSettings::setIDBeginChunkAudio(uint32_t idChunk) {
	m_idBeginChunkAudio = idChunk;
}

void SingletonSettings::setIDEndChunkAudio(uint32_t idChunk) {
	m_idEndChunkAudio = idChunk;
}

void SingletonSettings::setIDBeginChunkVideo(uint32_t idChunk) {
	m_idBeginChunkVideo = idChunk;
}

void SingletonSettings::setIDEndChunkVideo(uint32_t idChunk) {
	m_idEndChunkVideo = idChunk;
}

uint32_t SingletonSettings::getIDBeginChunkAudio() {
	return m_idBeginChunkAudio;
}

uint32_t SingletonSettings::getIDEndChunkAudio() {
	return m_idEndChunkAudio;
}

uint32_t SingletonSettings::getIDBeginChunkVideo() {
	return m_idBeginChunkVideo;
}

uint32_t SingletonSettings::getIDEndChunkVideo() {
    return m_idEndChunkVideo;
}

uint32_t SingletonSettings::getOffsetAudioChunk(double fractPos)
{
    if((fractPos>=0)&&(fractPos<0.25f)){
        return 0;
    }
    else if((fractPos>=0.25f)&&(fractPos<0.5f)){
        return 1;
    }else if((fractPos>=0.5f)&&(fractPos<0.75f)){
        return 2;
    }else{
        return 3;
    }
}

uint32_t SingletonSettings::getIdEndChunkWithIFrame() const
{
    return m_idEndChunkWithIFrame;
}

uint32_t SingletonSettings::getIdBegChunkWithIFrame() const
{
    return m_idBegChunkWithIFrame;
}
