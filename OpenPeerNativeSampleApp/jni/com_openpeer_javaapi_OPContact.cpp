#include "com_openpeer_javaapi_OPStackMessageQueue.h"
#include "openpeer/core/IContact.h"
#include "openpeer/core/IHelper.h"
#include "openpeer/core/ILogger.h"

#include "globals.h"

using namespace openpeer::core;

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    toDebugString
 * Signature: (Lcom/openpeer/javaapi/OPContact;Z)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_openpeer_javaapi_OPContact_toDebugString
(JNIEnv *, jclass, jobject, jboolean);

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    createFromPeerFilePublic
 * Signature: (Lcom/openpeer/javaapi/OPAccount;Ljava/lang/String;)Lcom/openpeer/javaapi/OPContact;
 */
JNIEXPORT jobject JNICALL Java_com_openpeer_javaapi_OPContact_createFromPeerFilePublic
(JNIEnv *env, jclass, jobject account, jstring peerFilePublic)
{
	jclass cls;
	jmethodID method;
	jobject object;
	JNIEnv *jni_env = 0;
	IContactPtr contactPtr;

	const char *peerFilePublicStr;
	peerFilePublicStr = env->GetStringUTFChars(peerFilePublic, NULL);
	if (peerFilePublicStr == NULL) {
		return object;
	}

	if(accountPtr)
	{
		ElementPtr peerFileElement = IHelper::createElement(peerFilePublicStr);
		contactPtr = IContact::createFromPeerFilePublic(accountPtr, IHelper::createPeerFilePublic(peerFileElement));
	}

	if(contactPtr)
	{
		jni_env = getEnv();
		if(jni_env)
		{
			cls = findClass("com/openpeer/javaapi/OPContact");
			method = jni_env->GetMethodID(cls, "<init>", "()V");
			object = jni_env->NewObject(cls, method);
			contactMap.insert(std::pair<jobject, IContactPtr>(object, contactPtr));

		}
	}
	return object;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    getForSelf
 * Signature: (Lcom/openpeer/javaapi/OPAccount;)Lcom/openpeer/javaapi/OPContact;
 */
JNIEXPORT jobject JNICALL Java_com_openpeer_javaapi_OPContact_getForSelf
(JNIEnv *, jclass, jobject)
{
	jclass cls;
	jmethodID method;
	jobject object;
	JNIEnv *jni_env = 0;
	IContactPtr contactPtr;

	if(accountPtr)
	{
		contactPtr = IContact::getForSelf(accountPtr);
	}

	if(contactPtr)
	{
		jni_env = getEnv();
		if(jni_env)
		{
			cls = findClass("com/openpeer/javaapi/OPContact");
			method = jni_env->GetMethodID(cls, "<init>", "()V");
			object = jni_env->NewObject(cls, method);
			contactMap.insert(std::pair<jobject, IContactPtr>(object, contactPtr));

		}
	}
	return object;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    getStableID
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_openpeer_javaapi_OPContact_getStableID
(JNIEnv *, jobject owner)
{
	jlong ret = 0;
	std::map<jobject, IContactPtr>::iterator it = contactMap.find(owner);
	if (it!= contactMap.end())
	{
		ret = it->second->getID();
	}
	return ret;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    isSelf
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_openpeer_javaapi_OPContact_isSelf
(JNIEnv *, jobject owner)
{
	jboolean ret;
	std::map<jobject, IContactPtr>::iterator it = contactMap.find(owner);
	if (it!= contactMap.end())
	{
		ret = it->second->isSelf();
	}
	return ret;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    getPeerURI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_openpeer_javaapi_OPContact_getPeerURI
(JNIEnv *env, jobject owner)
{
	jstring ret;
	std::map<jobject, IContactPtr>::iterator it = contactMap.find(owner);
	if (it!= contactMap.end())
	{
		ret = env->NewStringUTF(it->second->getPeerURI().c_str());
	}
	return ret;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    getPeerFilePublic
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_openpeer_javaapi_OPContact_getPeerFilePublic
(JNIEnv *env, jobject owner)
{
	jclass cls;
	jmethodID method;
	jobject object;
	JNIEnv *jni_env = 0;
	jstring ret;
	std::map<jobject, IContactPtr>::iterator it = contactMap.find(owner);
	if (it!= contactMap.end())
	{
		jni_env = getEnv();
		if(jni_env)
		{
			ElementPtr peerFilePublic = IHelper::convertToElement(it->second->getPeerFilePublic());
			ret = env->NewStringUTF(IHelper::convertToString(peerFilePublic).c_str());

			//TODO export peer file public to ElementPtr and then convert to String
			jclass peerFileCls = findClass("com/openpeer/javaapi/OPPeerFilePublic");
			jmethodID peerFileMethodID = jni_env->GetMethodID(peerFileCls, "<init>", "()V");
			jobject peerFileObject = jni_env->NewObject(peerFileCls, peerFileMethodID);
		}
	}
	return ret;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    getAssociatedAccount
 * Signature: ()Lcom/openpeer/javaapi/OPAccount;
 */
JNIEXPORT jobject JNICALL Java_com_openpeer_javaapi_OPContact_getAssociatedAccount
(JNIEnv *, jobject)
{
	return globalAccount;
}

/*
 * Class:     com_openpeer_javaapi_OPContact
 * Method:    hintAboutLocation
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_openpeer_javaapi_OPContact_hintAboutLocation
(JNIEnv *env, jobject owner, jstring locationId)
{
	const char *locationIdStr;
	locationIdStr = env->GetStringUTFChars(locationId, NULL);
	if (locationIdStr == NULL) {
		return;
	}

	std::map<jobject, IContactPtr>::iterator it = contactMap.find(owner);
	if (it!= contactMap.end())
	{
		it->second->hintAboutLocation(locationIdStr);
	}
}

#ifdef __cplusplus
}
#endif
